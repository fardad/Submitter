#ifndef SENECA_SUBMITTER_H_
#define SENECA_SUBMITTER_H_
#include "debug.h"
#include "Vals.h"
#include "SubVals.h"
#include "Command.h"
#include "Date.h"
#include "User.h"
#include "subValues.h"


#define isSpace(ch) ((ch) < 33 || (ch) > 126)

namespace seneca{
  class Submitter{
    User m_user;
    bool m_ok2submit;
    bool m_late;
    bool m_skipSpaces;
    bool m_skipNewlines;
    bool m_dueOnly;
    bool m_feedbackOnly;
    bool m_memLeak;
    std::string m_lateTitle;
    int m_accommExtension;
    int m_accommExtMins;
    std::string m_accommTitle;
    Date m_now;
    Date m_dueDate;
    Date m_rejectionDate;
    Date m_publishDate;
    int m_argc;
    char** m_argv;
    std::string m_home;
    std::string m_submitterDir;
    std::string m_configFileName;
    std::string m_archiveDir;
    SubVals m_asVals;
    SubVals m_accom;
    Command m_cls;
    void setSubmitterDir();
    void clrscr()const;
    bool yes()const;
    bool getAssignmentValues();
    bool assignmentMatch(std::string assignmentName)const;
    bool getAccommodation();
    bool copyProfFiles();
    bool archiveFiles();
    bool filesExist();
    bool compareOutputs(int from, int to);
    bool lineCompare(const char *student, const char* professor,int& stdUnmatchedIndex, int& profUnmatchedIndex);
    bool compare(const char* stdnt, const char* prof, int line);
    void diff(std::ostream& os, const char* stdnt, const char* prof, int line, int stdUnmatchedIndex, int profUnmatchedIndex);
    int compile();
    int execute();
    int checkOutput();
    bool skipLine(int lineNo);
    const char* name();
    bool submit(std::string& toEmail, bool Confirmation = false); // if confirmation is ture then work will be submitted to student
    bool removeBS(const char* filename);
    static const char* getFilename(const char* path);
    void printCommandSyntaxHelp()const;
    bool checkAndSetOption(std::string option);
    static bool isEmptyLine(const char* line);
    int printDueDates();
    int error(int no, const char* message, bool report = true);
  public:
    Submitter(int argc, char** argv);
    int run();
  };
}
#endif