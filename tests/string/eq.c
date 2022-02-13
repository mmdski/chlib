#include "test.h"
#include <chl.h>

int
main ()
{
  ChlString a      = chl_string_new ("abcd");
  ChlString b      = chl_string_new ("efgh");
  ChlString c      = NULL;
  ChlString a_copy = chl_string_copy (a);

  assert_true (chl_string_eq (a, a));
  assert_false (chl_string_eq (a, c));
  assert_false (chl_string_eq (a, b));
  assert_false (a == a_copy);
  assert_true (chl_string_eq (a, a_copy));
  assert_false (chl_string_eq (NULL, NULL));

  assert_zero (chl_string_free (a));
  assert_zero (chl_string_free (b));
  assert_zero (chl_string_free (a_copy));

  return EXIT_SUCCESS;
}
