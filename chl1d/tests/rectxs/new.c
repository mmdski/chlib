#include <stdlib.h>

#include <chl/chl1d.h>
#include <chl/chlerror.h>

#include "test.h"

int
main (void)
{
  double width = 10;

  Chl1DRectXS xs = chl_1d_rectxs_new (width);
  assert_nonnull (xs);
  assert_zero (chl_1d_rectxs_free (xs));

#ifdef CHECK_ARGS
  xs = NULL;
  xs = chl_1d_rectxs_new (-10);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  xs = chl_1d_rectxs_new (0);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();
#endif

  return EXIT_SUCCESS;
}
