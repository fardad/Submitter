#ifndef SENECA_LOG_H
#define SENECA_LOG_H
#include <iostream>
#include <fstream>
#include <string>
namespace seneca {
   class LogFile;
   class Log {
      char m_delivarable[256]{};
      size_t m_noOfTries{};
      size_t m_noOfSubmission{};
      Log() = default;
   public:
      Log& operator=(const char* delivarable);
      bool operator==(const char* delivarable)const;
      bool operator!=(const char* delivarable)const;
      operator const char* ()const;
      operator char* ();
      std::ofstream& write(std::ofstream& file);
      std::ifstream& read(std::ifstream& file);
      size_t submit();
      size_t operator++();
      std::string tostring()const;
      operator std::string()const;
      friend class LogFile;
   };

   class LogFile {
      std::string m_filename;
      size_t m_semster{};
      Log* m_logs{};
      size_t m_noOfLogs{};
      bool m_badfile{};
      Log& operator++(); // add log
      LogFile& load();
      void clear();
      bool m_saved{};
   public:
      LogFile(const char* filename);
      ~LogFile();
      Log& operator[](size_t index);
      Log& operator[](const char* delivarable);
      Log& operator[](std::string delivarable);
      Log& log(size_t index);
      LogFile& save();
      bool badFile()const;
   };
}
#endif // !SENECA_LOG_H


