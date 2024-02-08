#include <iostream>
#include "Log.h"
using namespace std;
using namespace seneca;
int main() {
   LogFile F("logText.bin");
   for (int i = 0; i < 10; i++) {
      ++F["244/w2/p1"];
   }
   for (int i = 0; i < 3; i++) {
      F["244/w2/p1"].submit();
   }
   for (int i = 0; i < 5; i++) {
      ++F["244/w5/p1"];
   }
   for (int i = 0; i < 2; i++) {
      F["244/w5/p1"].submit();
   }
   cout << F["244/w5/p1"].tostring() << endl;
   cout << F["244/w2/p1"].tostring() << endl;
   return 0;
}