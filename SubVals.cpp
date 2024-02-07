#include "Vals.h"
#include "SubVals.h"
using namespace std;
namespace seneca{
  SubVal::SubVal(std::string& key, Vals& value){
    m_key = key;
    m_value = value;
  }
  void SubVals::add(string key, Vals value){
    m_vals.push_back(SubVal(key, value));
  }
  string& SubVals::operator[](int index){
    return m_vals[index % m_vals.size()].m_key;
  }
  bool SubVals::exist(const char* key)const{
    bool ret = false;
    unsigned i = 0;
    for (i = 0; ret == false && i < m_vals.size(); i++){
      ret = (m_vals[i].m_key == key);
    }
    return ret;
  }
  Vals& SubVals::operator[](const char* key) {
    Vals* sv = &m_nothing;
    unsigned i = 0;
    for (i = 0; i < m_vals.size() && sv->size() == 0; i++) {
      if (m_vals[i].m_key == key) {
        sv = &m_vals[i].m_value;
      }
    }
    return *sv;
  }
  Vals& SubVals::values(int index) {
    return m_vals[index % m_vals.size()].m_value;
  }
  int SubVals::size(){
    return m_vals.size();
  }

}