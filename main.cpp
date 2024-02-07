#define _CRT_SECURE_NO_WARNINGS
#include "Submitter.h"

int main(int argc, char* argv[]){
  //set new shell environmental variable using putenv
  char lc_all[] = "LC_ALL=en_CA.UTF-8";
  char lc_col[] = "LC_COLLATE=en_CA.UTF-8";
  putenv(lc_all);
  putenv(lc_col);
  seneca::Submitter S(argc, argv);
  return S.run();
}