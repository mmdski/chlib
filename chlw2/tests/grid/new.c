#include <stdlib.h>

#include <chl/chlerror.h>
#include <chl/chlw2.h>

#include "test.h"

int
main (void)
{
  int n_segments = 10;
  int n_layers   = 10;

  ChlW2Grid g = chl_w2_grid_new (n_segments, n_layers, 0, 0, 0, 0);
  assert_nonnull (g);
  assert_false (chl_err_stack_is_err ());

  chl_w2_grid_free (g);

  assert_null (chl_w2_grid_new (-1, n_layers, 0, 0, 0, 0));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_null (chl_w2_grid_new (n_segments, -1, 0, 0, 0, 0));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_null (chl_w2_grid_new (-1, -1, 0, 0, 0, 0));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
