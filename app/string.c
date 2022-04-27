#include <stdio.h>
#include <stdlib.h>

#include <chl/chlstring.h>

int
main (void)
{
  ChlString s = chl_string_new ("Hello, world!");
  char     *string;

  if (chl_string_get (s, &string) < 0)
    return EXIT_FAILURE;

  printf ("%s\n", string);

  long len;
  if (chl_string_len (s, &len) < 0)
    return EXIT_FAILURE;

  printf ("The string is %ld characters long\n", len);

  chl_string_free (s);

  return EXIT_SUCCESS;
}
