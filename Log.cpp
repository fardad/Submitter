#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include <sstream>
#include "Command.h"
#include "Log.h"
#include "subValues.h"
#include "Date.h"

using namespace std;
namespace seneca {
   Log& Log::operator=(const char* delivarable) {
      delivarable&& strcpy(m_delivarable, delivarable);
      return *this;
   }
   bool Log::operator==(const char* delivarable) const
   {
      return delivarable && m_delivarable && strcmp(delivarable, m_delivarable) == 0;
   }
   bool Log::operator!=(const char* delivarable) const
   {
      return !operator==(delivarable);
   }
   Log::operator const char* () const {
      return reinterpret_cast<const char*>(this);
   }

   Log::operator char* () {
      return reinterpret_cast<char*>(this);
   }

   std::ofstream& Log::write(std::ofstream& file) {
      Log lenc = *this;
      Command::enc(lenc, SUB_LOG_DIR, sizeof(lenc));
      file.write(lenc, sizeof(lenc));
      return file;
   }

   std::ifstream& Log::read(std::ifstream& file) {
      file.read(*this, sizeof(*this));
      Command::dec(*this, SUB_LOG_DIR, sizeof(*this));
      return file;
   }

   size_t Log::submit() {
      return ++m_noOfSubmission;
   }

   size_t Log::operator++() {
      return ++m_noOfTries;
   }

   std::string Log::tostring() const {
      std::stringstream ss;
      ss << m_delivarable << ": " << m_noOfTries << " unsuccessful tries and " << m_noOfSubmission << " successful submissions";
      return ss.str();
   }

   Log::operator std::string() const {
      return tostring();
   }

   Log& LogFile::operator++() {
      size_t i{};
      Log* temp = new Log[++m_noOfLogs];
      for (i = 0; i < m_noOfLogs - 1; i++) {
         temp[i] = m_logs[i];
      }
      delete[] m_logs;
      m_logs = temp;
      return m_logs[i];
   }

   LogFile& LogFile::load() {
      clear();
      ifstream file(m_filename);
      if (file) {
         file.read(reinterpret_cast<char*>(&m_semster), sizeof(m_semster));
         if (m_semster != static_cast<size_t>(Date().semester())) {
            m_semster = Date().semester();
         }
         else {
            file.seekg(streamoff(0), ios::end);
            size_t size = static_cast<size_t>(file.tellg()) - sizeof(m_semster);
            size = size / sizeof(Log);
            file.seekg(sizeof(m_semster));
            for (size_t i = 0; i < size; i++) {
               file.read(operator++(), sizeof(Log));
               Command::dec(log(i), SUB_LOG_DIR, sizeof(Log));
            }
         }
      }
      return *this;
   }

   LogFile& LogFile::save() {
      if (!m_saved) {
         m_saved = true;
         ofstream file(m_filename);
         file.write(reinterpret_cast<const char*>(&m_semster), sizeof(m_semster));
         for (size_t i = 0; i < m_noOfLogs; i++) {
            Command::enc(log(i), SUB_LOG_DIR, sizeof(Log));
            file.write(log(i), sizeof(Log));
         }
      }
      return *this;
   }

   void LogFile::clear() {
      delete[] m_logs;
      m_logs = nullptr;
      m_noOfLogs = 0u;
      m_semster = static_cast<size_t>(Date().semester());
   }

   LogFile::LogFile(const char* filename) :m_filename(filename),
      m_semster(static_cast<size_t>(Date().semester())) {
      load();
   }

   LogFile::~LogFile() {
      save();
      clear();
   }

   Log& LogFile::operator[](size_t index) {
      return m_logs[index % m_noOfLogs];
   }

   Log& LogFile::operator[](const char* delivarable){
      size_t i;
      Log* element{};
      for (i = 0; (m_logs[i] != delivarable) && i < m_noOfLogs; i++);
      if (i == m_noOfLogs) {
         element = &operator++();
         *element = delivarable;
      }
      else {
         element = &log(i);
      }
      return *element;
   }

   Log& LogFile::operator[](std::string delivarable){
      return operator[](delivarable.c_str());
   }

   Log& LogFile::log(size_t index)
   {
      return m_logs[index % m_noOfLogs];
   }
}