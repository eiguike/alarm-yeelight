#ifndef LOGGER_INTERNALS_H
#define LOGGER_INTERNALS_H

#include "logger.h"

typedef struct LOGGER_INTERNAL_STRUCTURE {
  void (*Dispose) (struct LOGGER_INTERNAL_STRUCTURE* This);
  void (*Info) (struct LOGGER_INTERNAL_STRUCTURE* This, const char* Format, ...);
  void (*Debug) (struct LOGGER_INTERNAL_STRUCTURE* This, const char* Function, int Line, const char* Format, ...);
  void (*Error) (struct LOGGER_INTERNAL_STRUCTURE* This, const char* Function, int Line, const char* Format, ...);
  void (*Warning) (struct LOGGER_INTERNAL_STRUCTURE* This, const char* Format, ...);

  OUTPUT Output;
  FILE * FileBuffer;
} LOGGER_INTERNAL;

#endif
