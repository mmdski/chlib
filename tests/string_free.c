#include "chlassert.h"
#include <chl/chl_string.h>

int
main (void)
{
  ChlString s = chl_string_new ("Hello, world!");
  chl_string_free (s);

  chl_string_free (NULL);

  return EXIT_SUCCESS;
}
