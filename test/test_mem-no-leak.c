#include <stdlib.h>
void *p;
int
main (void)
{
  p = malloc (7);
  free (p);
  return 0;
}
