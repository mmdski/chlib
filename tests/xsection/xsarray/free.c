#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main ()
{

  int  n   = 4;
  real y[] = { 1, 0, 0, 1 };
  real z[] = { 0, 0, 1, 1 };

  ChlXSArray a = chl_xs_array_new (n, y, z);
  assert_nonnull (a);
  assert_false (chl_err_stack_is_err ());
  assert_zero (chl_xs_array_free (a));
  a = NULL;

  assert_negative (chl_xs_array_free (NULL));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  return EXIT_SUCCESS;
}
