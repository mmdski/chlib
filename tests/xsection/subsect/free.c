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

  real         roughness = 0.035;
  ChlXSSubsect ss        = chl_xs_subsect_new (a, roughness);
  assert_nonnull (ss);
  assert_zero (chl_xs_subsect_free (ss));

  ss = NULL;
  assert_negative (chl_xs_subsect_free (ss));
  assert_true (chl_err_stack_is_err ());
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  chl_xs_array_free (a);

  return EXIT_SUCCESS;
}
