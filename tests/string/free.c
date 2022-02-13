#include "test.h"
#include <chl.h>

int
main ()
{
  ChlString s = chl_string_new ("Hello, world!");
  assert_zero (chl_string_free (s));

  assert_negative (chl_string_free (NULL));

  return EXIT_SUCCESS;
}
