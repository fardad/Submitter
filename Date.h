#ifndef SENECA_DATE_H__
#define SENECA_DATE_H__
#include <iostream>
#include <sstream>
#include "debug.h"
namespace seneca{
  const int NO_ERROR = 0;
  const int CIN_FAILED = 1;
  const int YEAR_ERROR = 2;
  const int MON_ERROR = 3;
  const int DAY_ERROR = 4;
  const int HOUR_ERROR = 5;
  const int  MIN_ERROR = 6;
  const bool DATE_ONLY = true;
  class Date{
  private:
    static const char dayName[7][10];
    int m_year;
    int m_mon;
    int m_day;
    int m_hour;
    int m_min;
    int m_readErrorCode;
    int daysValue()const;
    long long uniqueValue()const;
    int curYear()const;
    bool validate();
    void errCode(int);
    void set(int year, int mon, int day, int hour, int min);
  public:
    Date();
    Date(int year, int mon, int day);
    Date(int year, int mon, int day, int hour, int min = 0);
    Date(std::stringstream& theDate);
    void set();
    const char* weekday()const;
    bool operator==(const Date& D)const;
    bool operator!=(const Date& D)const;
    bool operator<(const Date& D)const;
    bool operator>(const Date& D)const;
    bool operator<=(const Date& D)const;
    bool operator>=(const Date& D)const;
    bool sameDate(const Date& D)const;
    Date& operator++();
    Date& addMin();
    Date& operator+=(int days); //adds number of days to the date;
    int operator-(const Date & D)const;
    Date& addMin(int minutes);
    std::istream& read(std::istream& is = std::cin);
    std::ostream& write(std::ostream& os = std::cout)const;
    int errCode()const;
    bool bad()const;
    int mdays()const;
    int semester() const;
  };

  std::ostream& operator<<(std::ostream& os, const Date& RO);
  std::istream& operator>>(std::istream& is, Date& RO);
}
#endif