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
  chl_xs_array_free (a);

  real n_value;
  assert_zero (chl_xs_subsect_roughness (ss, &n_value));
  assert_equal (roughness, n_value);

  chl_xs_subsect_free (ss);

  return EXIT_SUCCESS;
}
