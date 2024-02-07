#ifndef SENECA_VALS_H_
#define SENECA_VALS_H_

#include <fstream>
#include <string>
#include <vector>
#include "debug.h"

namespace seneca{
  // a class to parse and hold delimeter seperated values
  // a delimeter can not be a white space character
  class Vals :public std::string{
    std::string m_nothing;
    char m_delim;
    std::vector<std::string> m_values;
    void set();
    static std::string trim(std::string s);
  public:
    void set(const char* str, char delim = 0);
    void set(char delim );
    int size();
    Vals(char delimeter = ',');
    Vals(std::string csv, char delimeter);
    std::string& operator[](int index);
    void clear();
  };
  std::ifstream& operator>>(std::ifstream& ifstr, Vals& V);
}

#endif