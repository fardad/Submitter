#include <cstdlib>
#include <cstring>
#include "Command.h"

# ifdef SENECA_DEBUG
#   include <iostream>
# endif


using namespace std;
namespace seneca{
  Command::Command(string str) : string(str){
  }
  int Command::run()const{
# ifdef SENECA_DEBUG
    cout <<"RUN: "<< c_str() << endl;
    return 0;
# else
    return system(c_str());
# endif
  }
  void Command::dec(char* str, const char* key, size_t n) {
     unsigned char data;
     size_t m = strlen(key);
     for (size_t i = 0; i < n; i++) {
        data = static_cast<unsigned char>(str[i]);
        str[i] = (data >> 1) | (data << 7);
        str[i] = str[i] ^ key[i % m];
     }
  }
  size_t Command::enc(char* str, const char* key) {
     unsigned char data;
     size_t n = strlen(str);
     size_t m = strlen(key);
     for (size_t i = 0; i < n; i++) {
        str[i] = str[i] ^ key[i % m];
        data = static_cast<unsigned char>(str[i]);
        str[i] = (data << 1) | (data >> 7);
     }
     return n;
  }
}


