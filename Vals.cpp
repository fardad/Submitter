#include <cctype>
#include "Vals.h"
using namespace std;
namespace seneca{
  string Vals::trim(string s){
    size_t cur = 0;
    while (s.length() != 0 && isspace(s.at(cur))){
      s.erase(cur, 1);
    }
    cur = s.length() - 1;
    while (s.length() != 0 && isspace(s.at(cur))){
      s.erase(cur, 1);
      cur = s.length() - 1;
    }
    return s;
  }
  Vals::Vals(char delim){
    m_delim = delim;
  }
  void Vals::set(const char* str, char delim){
    assign(str);
    if (delim) m_delim = delim;
    set();
  }
  void Vals::set(char delim){
    m_delim = delim;
    set();
  }
  void Vals::clear(){
    string::clear();
    m_values.clear();
  }
  void Vals::set(){
    size_t first = find_first_of(m_delim);
    size_t last = find_last_of(m_delim);
    m_values.clear();
    if (first != string::npos){
      if (first == last){
        m_values.push_back(trim(substr(0, first)));
        m_values.push_back(trim(substr(first + 1, length() - first)));
      }
      else{
        size_t from = 0;
        m_values.push_back(trim(substr(from, first)));
        while (first != last){
          from = first + 1;
          first = find_first_of(m_delim, from);
          m_values.push_back(trim(substr(from, first - from)));
        }
        m_values.push_back(trim(substr(first+1, length() - first)));
      }
    }
    else if (length() > 0){
      m_values.push_back(trim(*this));
    }
  }
  Vals::Vals(std::string csv, char delim) : std::string(csv){
    m_delim = delim;
    set();
  }
  int Vals::size(){
    return m_values.size();
  }
  string& Vals::operator[](int index){
    string* val = &m_nothing;
    if (size() > 0) val = &m_values[index%size()];
    return *val;
  }
  std::ifstream& operator>>(std::ifstream& ifstr, Vals& V){
    char line[4096] = "";
    ifstr.getline(line, 4095, '\n');
    V.clear();
    // not failed and not a comment
    if (!ifstr.fail() && !(line[0] == '-' && line[1] == '-')){
      V.set(line);
    }
    return ifstr;
  }

}