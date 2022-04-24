#include "test.h"
#include <chl.h>

int
main (void)
{
  int  n   = 4;
  real y[] = { 1, 0, 0, 1 };
  real z[] = { 0, 0, 1, 1 };

  ChlXSArray a = chl_xs_array_new (n, y, z);
  assert_nonnull (a);
  assert_false (chl_err_stack_is_err ());
  chl_xs_array_free (a);

  ChlXSArray b;
  b = chl_xs_array_new (n, NULL, z);
  assert_null (b);
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  b = chl_xs_array_new (n, y, NULL);
  assert_null (b);
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  // test non-ascending z
  b = chl_xs_array_new (n, y, y);
  assert_null (b);
  assert_true (chl_err_stack_is_type (VALUE_ERROR));
  chl_err_stack_clear ();

  return EXIT_SUCCESS;
}
