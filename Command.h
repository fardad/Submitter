#ifndef SENECA_COMMAND_H_
#define SENECA_COMMAND_H_

#include <string>
#include "debug.h"
namespace seneca{

  class Command :public std::string{
  public:
    Command(std::string str);
    int run()const;
    static void dec(char* str, const char* key, size_t n);
    static size_t enc(char* str, const char* key);
  };
}
#endif