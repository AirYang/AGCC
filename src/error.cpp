#include <cstdio>
#include <cstdlib>

#include "../include/error.h"

void error(const char* fileName, const char* funcName, int fileLine) {
  fprintf(stderr, "AGCC error filename[%s] funcname[%s] fileline[%d]\n",
          fileName, funcName, fileLine);
  exit(-1);
}