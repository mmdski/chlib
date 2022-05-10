#include <string.h>

#include <chl/chl_string.h>

#include "chlassert.h"

int
main (void)
{
  char     *string = "Hello, world!";
  ChlString s      = chl_string_new (string);

  char *get_string;
  assert_zero (chl_string_get (s, &get_string));
  assert_zero (strcmp (get_string, string));

  chl_string_free (s);

  return EXIT_SUCCESS;
}
