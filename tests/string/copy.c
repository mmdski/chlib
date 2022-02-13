#include "test.h"
#include <chl.h>
#include <string.h>

int
main ()
{
  ChlString s      = chl_string_new ("Hello, world!");
  ChlString s_copy = chl_string_copy (s);

  char *a;
  assert_zero (chl_string_get (s, &a));

  char *b;
  assert_zero (chl_string_get (s_copy, &b));

  assert_zero (strcmp (a, b));

  assert_zero (chl_string_free (s));
  assert_zero (chl_string_free (s_copy));

  return EXIT_SUCCESS;
}
