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
  chl_xs_array_free (a);

  double n_value;
  assert_zero (chl_xs_subsect_roughness (ss, &n_value));
  assert_equal (roughness, n_value);

  chl_xs_subsect_free (ss);

  return EXIT_SUCCESS;
}
