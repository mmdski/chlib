#include "test.h"
#include <chl.h>

int
main ()
{
  int  n1   = 4;
  real y1[] = { 1, 0, 0, 1 };
  real z1[] = { 0, 0, 1, 1 };

  ChlXSArray a1 = chl_xs_array_new (n1, y1, z1);
  assert_nonnull (a1);

  ChlXSArray a2 = chl_xs_array_copy (a1);
  assert_nonnull (a2);

  assert_true (chl_xs_array_eq (a1, a2));

  assert_null (chl_xs_array_copy (NULL));
  assert_true (chl_err_stack_is_err ());
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  chl_xs_array_free (a1);
  chl_xs_array_free (a2);

  return EXIT_SUCCESS;
}
