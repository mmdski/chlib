#include <chl.h>
#include <stdlib.h>

#include "test.h"

int
main (void)
{

  /* test errors */
  int  n           = 4;
  real z[]         = { 0, 0, 1, 1 };
  real y[]         = { 1, 0, 0, 1 };
  int  n_roughness = 1;
  real roughness   = 0.035;

  ChlXSCompound xs;

  /* invalid number of coordinates */
  xs = chl_xs_comp_new (n, y, z, 1, &roughness, NULL);
  assert_nonnull (xs);
  chl_xs_comp_free (xs);

  chl_xs_comp_free (NULL);

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
