#include <fstream>
#include <iostream>
#include "debug.h"
#include "colors.h"
#include "Command.h"
#include "User.h"

#define WHO_COMMAND_NAME "mwho"
using namespace std;
namespace seneca {
  User::User() {
    m_multipleIp = false;
#ifdef  SENECA_DEBUG
    m_userid.assign("debug_id");
    m_uid = 1234;
#else
    uid_t uid = getuid();
    m_uid = (unsigned int)uid;
    struct passwd *pw = getpwuid(uid);
    if (pw) {
      m_userid.assign(pw->pw_name);
    }
    else {
      m_userid.assign("noid");
      m_uid = 0;
    }
#endif //  SENECA_DEBUG
  }
  bool User::multipleLogins()const {
    return m_multipleIp;
  }
  const string& User::ip()const {
    return m_ip;
  }
  std::string User::userid() const{
     return m_userid;
  }
  void User::getIP() {
    int logins = 0;
    string token;
    cout << col_yellow << "Please wait, loading user location information...." << endl;
    Command C(WHO_COMMAND_NAME);
    C += " > who.txt";
    C.run();
    ifstream who("who.txt");
    while (who >> token) {
      if (token == m_userid) {
        who >> token >> token >> token >> token;
        remParentheses(token);
        if (logins) {
          if (token != m_ip) {
            m_multipleIp = true;
            m_ip = token;
          }
        }
        else {
          m_ip = token;
        }
        logins++;
      }
    }
    who.clear();
    who.close();
    cout << "Done!" << endl;
    Command("rm who.txt").run();
  }
  void User::remParentheses(std::string& ip)const {
    ip = ip.substr(1, ip.size() - 2);
  }
  bool User::operator==(unsigned int uid)const {
    return uid == m_uid;
  }

  bool User::operator==(string userid)const {
    return m_userid == userid;
  }
  bool User::operator==(const char* userid)const {
    return m_userid == string(userid);
  }
  bool User::operator==(const User& U)const {
    return m_userid == U.m_userid;
  }
  bool User::valid()const {
    return m_uid != 0;
  }
  std::ostream& User::print(std::ostream& os) const {
    return os << m_userid << ": " << m_uid;
  }
  std::ostream& operator<<(std::ostream& os, const User& U) {
    return U.print(os);
  }

}