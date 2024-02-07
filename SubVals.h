#ifndef SENECA_SUBVALS_H__
#define SENECA_SUBVALS_H__
#include <string>
#include <vector>
#include "debug.h"
#include "Vals.h"
namespace seneca{
  class SubVals;
  class SubVal{
    std::string m_key;
    Vals m_value;
    SubVal(std::string& key, Vals& value);
    friend class SubVals;
  };
  class SubVals{
    Vals m_nothing;
    std::vector<SubVal> m_vals;
  public:
    void add(std::string key, Vals value);
    bool exist(const char* key)const;
    Vals& operator[](const char* key);
    std::string& operator[](int index);
    Vals& values(int index);
    int size();
  };
}

#endif