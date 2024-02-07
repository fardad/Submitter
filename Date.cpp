#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
namespace seneca{
  const char Date::dayName[7][10] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
  };
  const char* Date::weekday()const {
    std::tm time_in = { 1, 1, 1, // second, minute, hour
        m_day, m_mon-1,m_year - 1900 };
    // 1-based day, 0-based month, year since 1900

    std::time_t time_temp = std::mktime(&time_in);

    //Note: Return value of localtime is not threadsafe, because it might be
    // (and will be) reused in subsequent calls to std::localtime!
    const std::tm * time_out = std::localtime(&time_temp);

    //Sunday == 0, Monday == 1, and so on ...
    return Date::dayName[time_out->tm_wday];
  }
  int Date::curYear()const {
    time_t t = time(NULL);
    tm lt = *localtime(&t);
    return lt.tm_year + 1900;
  }
  void Date::set(){
    time_t t = time(NULL);
    tm lt = *localtime(&t);
    m_day = lt.tm_mday;
    m_mon = lt.tm_mon + 1;
    m_year = lt.tm_year + 1900;
    m_hour = lt.tm_hour;
    m_min = lt.tm_min;
    errCode(NO_ERROR);
  }

  void Date::set(int year, int mon, int day, int hour, int min){
    m_year = year;
    m_mon = mon;
    m_day = day;
    m_hour = hour;
    m_min = min;
    errCode(NO_ERROR);
  }

  int Date::daysValue()const{
     int a = (14 - m_mon) / 12;
     int y = m_year + 4800 - a;
     int m = m_mon + 12 * a - 3;
     return m_day + ((153 * m + 2) / 5) + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
  }
  bool Date::validate(){
    errCode(NO_ERROR);
    if (m_year < curYear()-1 || m_year > curYear()+ 1){
      errCode(YEAR_ERROR);
    }
    else if (m_mon < 1 || m_mon > 12){
      errCode(MON_ERROR);
    }
    else if (m_day < 1 || m_day > mdays()){
      errCode(DAY_ERROR);
    }
    else if (m_hour < 0 || m_hour > 23){
      errCode(HOUR_ERROR);
    }
    else if (m_min < 0 || m_min > 59){
      errCode(MIN_ERROR);
    }
    return !bad();
  }
  int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
    mon--;
    return days[mon] + int((mon == 1)*((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
  }
  int Date::semester() const {
     int syear = (m_year % 100 + 200)*10;
     if (m_mon <= 5 && *this < Date(m_year, 5, 10)) {
        syear += 1;
     }
     else if (*this < Date(m_year, 9, 10)) {
        syear += 4;
     }
     else if (*this < Date(m_year + 1, 1, 10)) {
        syear += 7;
     }
     return syear;
  }
  Date::Date(){
    set();
  }
  Date::Date(int year, int mon, int day){
    set(year, mon, day, 23, 59);
  }
  Date::Date(int year, int mon, int day, int hour, int min ){
    set(year, mon, day, hour, min);
  }
  Date::Date(std::stringstream& theDate) {
    read(theDate);
  }
  void Date::errCode(int readErrorCode){
    m_readErrorCode = readErrorCode;
  }
  int Date::errCode()const{
    return m_readErrorCode;
  }
  bool Date::bad()const{
    return m_readErrorCode != 0;
  }
  bool Date::operator==(const Date& D)const{
    return daysValue() == D.daysValue();
  }
  bool Date::operator!=(const Date& D)const{
    return !operator==(D);
  }
  bool Date::operator<(const Date& D)const{
    return daysValue() < D.daysValue();
  }
  bool Date::operator>(const Date& D)const{
    return daysValue() > D.daysValue();
  }
  bool Date::operator<=(const Date& D)const{
    return !operator>(D);
  }
  bool Date::operator>=(const Date& D)const{
    return !operator<(D);
  }
  bool Date::sameDate(const Date& D)const {
    return D.m_day == m_day && D.m_mon == m_mon && D.m_year == m_year;
  }
  Date& Date::operator++() {
    m_day++;
    if (m_day > mdays()) {
      m_day = 1;
      m_mon++;
    }
    if (m_mon > 12) {
      m_mon = 1;
      m_year++;
    }
    return *this;
  }
  Date&  Date::operator+=(int days) { //adds number of days to the date;
    if (days > 0) {
      for (int i = 0; i < days; i++) {
        operator++();
      }
    }
    return *this;
  }
  int Date::operator-(const Date& D) const {
     return daysValue() - D.daysValue();
  }
  Date& Date::addMin() {
    m_min++;
    if (m_min > 59) {
      m_hour++;
      m_min = 0;
    }
    if (m_hour > 23) {
      m_hour = 0;
      operator++();
    }
    return *this;
  }
  Date&  Date::addMin(int mins) {
    if (mins > 0) {
      int days = mins / 1440;
      mins = mins % 1440;
      operator+=(days);
      for (int i = 0; i < mins; i++) {
        addMin();
      }
    }
    return *this;
  }

  istream& Date::read(istream& is){
    char ch = '!';
    m_readErrorCode = 0;
    is >> m_year;
    is.ignore();
    is >> m_mon;
    is.ignore();
    is >> m_day;
    is.get(ch);
    is >> m_hour;
    if (is.fail()) {
      is.clear();
      if(ch!='!') is.putback(ch);
      m_hour = 23;
      m_min = 59;
    }
    else{
      is.ignore();
      is >> m_min;
    }
    if (is.fail()){
      errCode(CIN_FAILED);
    }
    else{
      validate();
    }
    return is;
  }

  ostream& Date::write(ostream& os)const{
    os <<weekday()<<", "<< right << m_year << "/" << setw(2) << setfill('0') << m_mon << "/"
      << setw(2) << setfill('0') << m_day;
      os <<" - " << setw(2) << setfill('0') << m_hour << ":" << setw(2) << setfill('0') << m_min;
    return os;
  }
  ostream& operator<<(ostream& os, const Date& RO){
    return RO.write(os);
  }
  istream& operator>>(istream& is, Date& RO){
    return RO.read(is);
  }


}
