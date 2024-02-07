#include <iostream>
#include "Vals.h"
using namespace std;
using namespace ict;
int main(){
  Vals V("   Key =  Value = v2 = v3=v4  ", '=');
  cout << V.size() << endl;
  int i;
  for (i = 0; i < V.size(); i++){
    cout <<"*"<< V[i] <<"*"<< endl;
  }
  return 0;
}
