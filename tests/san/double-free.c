// silence clang --analyze warning for this file
#ifndef __clang_analyzer__
#define __clang_analyzer__

#include <stdlib.h>
void *p;
int
main (void)
{
  p = malloc (7);
  free (p);
  free (p);
  return 0;
}

#endif
