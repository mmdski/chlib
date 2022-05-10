#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "chlassert.h"

int
main (void)
{

  /* test errors */
  int    n           = 4;
  double z[]         = { 0, 0, 1, 1 };
  double y[]         = { 1, 0, 0, 1 };
  int    n_roughness = 1;
  double roughness   = 0.035;

  Chl1DCompXS xs;

  /* invalid number of coordinates */
  xs = chl_xs_comp_new (n, y, z, n_roughness, &roughness, NULL);
  assert_nonnull (xs);
  chl_xs_comp_free (xs);

  chl_xs_comp_free (NULL);

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
