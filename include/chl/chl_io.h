#include <stdio.h>

#ifdef _MSC_VER

#define _BUFFER_COUNT 500

#define chl_sprintf(buffer, format, ...)                                       \
  sprintf_s (buffer, _BUFFER_COUNT, format, __VA_ARGS__)

#define chl_popen(command, mode) _popen (command, mode)

#else

#define chl_sprintf(buffer, format, ...) sprintf (buffer, format, __VA_ARGS__)

#define chl_popen(command, mode) popen (command, mode)

#endif
