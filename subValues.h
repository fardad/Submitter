#ifndef SENECA_SUBVALUES_H
#define SENECA_SUBVALUES_H

// define statements

//  version
#ifdef SUBMITTER_VERSION
# undef SUBMITTER_VERSION
#endif
#define SUBMITTER_VERSION "0.99.10.0"
#ifdef SUBMITTER_DATE
# undef SUBMITTER_DATE
#endif
#define SUBMITTER_DATE "2024-02-07"
//    program config file
#ifdef SUB_CFG_FILE
# undef SUB_CFG_FILE
#endif
#define SUB_CFG_FILE "submitter.cfg"

//    accommodation file
#ifdef SUB_ACC_FILE
# undef SUB_ACC_FILE
#endif
#define SUB_ACC_FILE "accommodations.cfg"

//    program default directory for assignment configuration files
#ifdef SUB_DEF_DIR
# undef SUB_DEF_DIR
#endif
#define SUB_DEF_DIR "submitter_files"

#ifdef SUB_ARCHIVE_DIR
# undef SUB_ARCHIVE_DIR
#endif
#define SUB_ARCHIVE_DIR "submitter"

#ifdef SUB_LOG_DIR
#  undef SUB_LOG_DIR
#endif
#define SUB_LOG_DIR "submitter/log"

#ifdef SUB_LOG_NAME
#undef SUB_LOG_NAME
#endif 
#define SUB_LOG_NAME ".sub_log"
#endif // !SENECA_SUBVALUES_H

