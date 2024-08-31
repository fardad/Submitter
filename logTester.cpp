#include <iostream>
#include "Log.h"
#include "Command.h"
using namespace std;
using namespace seneca;
bool submit(string toEmail);
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
   submit("fardad@fardad.com");
   return 0;
}

bool submit(string toEmail) {
   Command email("echo \"");
   bool include_output_in_email = false;
   email += "fsoleima";
   email += " ";
   email += "submission";
   email += " by `whoami`. Executed from ";
   email += " some direcotory ";
   email += "\" | mail -s \"";
   email += "OOP555 - ";
   email += "fsoleima";
   email += " submission by `whoami`\" ";
   email += " -Sreplyto=`whoami`@myseneca.ca ";
   if (true) {
      email += " -a attach.txt";
   }
   email += " " + toEmail;
#ifdef SENECA_DEBUGEMAIL
   cout << email << endl;
   return true;
#else
   return email.run() == 0;
#endif


}