#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Vals.h"
#include "SubVals.h"
using namespace std;
using namespace sict;

// define statements

//    program config file
#ifdef SUB_CFG_FILE
# undef SUB_CFG_FILE
#endif
#define SUB_CFG_FILE "submitter.cfg"


//    program default directory for assignment configuration files
#ifdef SUB_DEF_DIR
# undef SUB_DEF_DIR
#endif
#define SUB_DEF_DIR "sumbitter_files"


void setSubmitterDir(string & dir);
bool getAssignmentValues(SubVals& V, const char* asName, string& str);


int main(int argc, char* argv[], char* env[]){
  if (argc != 2){
    cout << "~prof_name.prof_lastname/submitter AssignmentName<ENTER>" << endl;
  }
  else{
    bool done = false;
    string submitterDir = SUB_DEF_DIR;
    setSubmitterDir(submitterDir);
    SubVals AsVals;
    if (!getAssignmentValues(AsVals, argv[1], submitterDir)){
      cout << "Can not find the assignment submission sepcs, please report this to your professor!" << endl;
    }
    else{
      int i, j = 0;
      for (i = 0; i < AsVals.size(); i++){
        cout << AsVals[i] << endl;
        for (j = 0; j < AsVals[AsVals[i].c_str()].size(); j++){
          cout << "--" << AsVals[AsVals[i].c_str()][j] << endl;
        }
      }
    }
  }
  return 0;
}
void setSubmitterDir(string & dir){
  bool done = false;
  Vals V('=');
  ifstream file(SUB_CFG_FILE);
  while (file && !done){
    file >> V;  // read a line of config file
    if (V.size() > 0){ // if any values read
      done = true;
      if (V[0] == "dir"){
        dir = V[1];
      }
    }
  }
  file.close();
}
bool getAssignmentValues(SubVals& SV, const char* asName, string& dir){
  bool ok = false;
  Vals V('|');
  string fname(dir + "/" + asName);
  fname += ".cfg";
  ifstream file(fname.c_str());
  while (file){
    file >> V;
    if (V.size() > 1){
      ok = true;
      SV.add(V[0], Vals(V[1], ','));
    }
  }
  file.close();
  return ok;
}
