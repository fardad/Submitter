#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Vals.h"
using namespace std;
using namespace ict;
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
int main(int argc, char* argv[], char* env[]){
  if (argc != 2){
    cout << "~prof_name.prof_lastname/submitter AssignmentName<ENTER>" << endl;
  }
  else{
    bool done = false;
    string submitterDir = SUB_DEF_DIR;
    setSubmitterDir(submitterDir);
    cout << submitterDir << endl;
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
