#ifndef SENECA_COLORS_H_
#define SENECA_COLORS_H_
#include "debug.h"

#ifndef SENECA_DEBUG
const char col_grey[] = "\e[38;5;8m";
const char col_red[] = "\e[38;5;9m";
const char col_green[] = "\e[38;5;10m";
const char col_yellow[] = "\e[38;5;11m";
const char col_blue[] = "\e[38;5;12m";
const char col_pink[] = "\e[38;5;13m";
const char col_cyan[] = "\e[38;5;14m";
const char col_white[] = "\e[38;5;15m";
const char col_end[] = "\e[0m";
#else
const char col_grey[] = "\033[38;5;8m";
const char col_red[] = "\033[38;5;9m";
const char col_green[] = "\033[38;5;10m";
const char col_yellow[] = "\033[38;5;11m";
const char col_blue[] = "\033[38;5;12m";
const char col_pink[] = "\033[38;5;13m";
const char col_cyan[] = "\033[38;5;14m";
const char col_white[] = "\033[38;5;15m";
const char col_end[] = "\033[0m";
#endif


#endif

