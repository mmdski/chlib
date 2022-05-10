#include <chl/chlerror.h>

#include "subsection.h"
#include "test.h"

int
main (void)
{
  int    n   = 4;
  double y[] = { 1, 0, 0, 1 };
  double z[] = { 0, 0, 1, 1 };

  ChlXSArray a = chl_xs_array_new (n, y, z);
  assert_nonnull (a);

  double       roughness = 0.035;
  ChlXSSubsect ss        = chl_xs_subsect_new (a, roughness);
  assert_nonnull (ss);
  assert_zero (chl_xs_subsect_free (ss));

  ss = chl_xs_subsect_new (NULL, roughness);
  assert_null (ss);
  assert_true (chl_err_stack_is_err ());
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  ss = chl_xs_subsect_new (a, -roughness);
  assert_null (ss);
  assert_true (chl_err_stack_is_err ());
  assert_true (chl_err_stack_is_type (VALUE_ERROR));
  chl_err_stack_clear ();

  chl_xs_array_free (a);

  return EXIT_SUCCESS;
}
