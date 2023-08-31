// silence clang --analyze warnings for this file
#ifndef __clang_analyzer__
#define __clang_analyzer__

#include <stdlib.h>
int *p;
int
main (void)
{
  p = malloc (7);
  free (p);
  *p = 10;
  return 0;
}

#endif
