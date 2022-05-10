#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "chlassert.h"

int
main (void)
{

  int    n   = 4;
  double y[] = { 1, 0, 0, 1 };
  double z[] = { 0, 0, 1, 1 };

  ChlXSArray a = chl_xs_array_new (n, y, z);
  assert_nonnull (a);
  assert_false (chl_err_stack_is_err ());
  chl_xs_array_free (a);
  a = NULL;

  chl_xs_array_free (NULL);
  assert_false (chl_err_stack_is_err ());

  return EXIT_SUCCESS;
}
