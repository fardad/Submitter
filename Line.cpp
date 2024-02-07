#include <cstring>
#include "Line.h"
#include "colors.h"
#include "debug.h"

namespace seneca {
  bool Line::m_colored = false;
  Line::Line(const char* line, int highLight):m_line(line), m_highlightIndex(highLight) {
  }
  std::ostream& Line::display(std::ostream& os)const {
    int i = 0;
    m_colored = (&os == &std::cout);
    while (m_line[i]) {
      if (i == m_highlightIndex && m_colored) os << col_red;
      if (m_line[i] == '\b') {  // don't think this is needed anymore since all the backspaces are removed!
        os << "\\b";
      }
      else {
        os << m_line[i];
      }
      if (i == m_highlightIndex && m_colored) os << col_end;
      i++;
    }
    if (m_highlightIndex >= 0) {
      os << std::endl;
      for (i = 0; i < m_highlightIndex; i++) os << " ";
      if (m_colored) os << col_red;
      os << "^" ;
      if (m_colored) os << col_end;
    }
    return os;
  }
  const char* Line::operator[](int index){
    m_buf[0] = 0;
    if (m_colored) copy(m_buf, col_red);
      cat(m_buf, charName( m_line[index]));
    if (m_colored) cat(m_buf, col_end);
    return m_buf;
  }
  void Line::copy(char* des, const char* src) {
    while (*src) *des++ = *src++;
    *des = 0;
  }
  void Line::cat(char* des, const char* src) {
    while (*des) des++;
    while (*src) *des++ = *src++;
    *des = 0;
  }
  void Line::cat(char* des, char src) {
    while (*des) des++;
    *des++ = src;
    *des = 0;
  }
  const char* Line::charName(char ch) {
    char chName[34][39] = {
      "Empty Line",
      "Start Of Heading",
      "Start Of Text",
      "End Of Text",
      "End Of Transmission",
      "Enquiry",
      "Acknoledge",
      "Bell (\\a)",
      "Backspace (\\b)",
      "Tab (\\t)",
      "New Line (\\n)",
      "Vertical Tab",
      "Form Feed (\\f)",
      "Newline (\\n) or Carriage Retrun (\\r)",
      "Shift out",
      "Shift in",
      "Data Link Escape",
      "Device Control 1",
      "Device Control 2",
      "Device Control 3",
      "Device Control 4",
      "Negative Acknoledge",
      "Synchronous Idle",
      "End of Tran. Block",
      "Cancel",
      "End Of Medium",
      "Substitude",
      "Escape",
      "File Separator",
      "Groupu Separator",
      "Record Separator",
      "Unit Separator",
      "Space",
      "Non printable char"
    };
    if (ch >= 33) {
      m_chName[0] = ch;
      m_chName[1] = '\0';
      ch = 33;
    }
    else {
      copy(m_chName, chName[int(ch)]);
    }
    return m_chName;
  }

  std::ostream& operator<<(std::ostream& os, const Line& L) {
    return L.display(os);
  }
}