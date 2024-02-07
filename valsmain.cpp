#include <iostream>
#include <fstream>
#include "Vals.h"
using namespace std;
using namespace ict;
int main(){
  ifstream file("vals.txt");
  Vals V('=');
  int i;
  while (file){
    file >> V;
    cout << V.size() << endl;
    for (i = 0; i < V.size(); i++){
      cout << "*" << V[i] << "*" << endl;
    }
    cout << "-------" << endl;
  }
  V.set("aa,b,ccc   , d, eeeee, f ,g   g, h", ',');
  cout << V.size() << endl;
  for (i = 0; i < 10; i++){
    cout << "*" << V[i] << "*" << endl;
  }
  cout << "-------" << endl;
  return 0;
}

