#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <chl/chlerror.h>
#include <chl/chlmath.h>
#include <chl/chlw2.h>

#include "test.h"

int
main (void)
{
  int n_segments = 10;
  int n_layers   = 5;

  real setvalue = 0;
  real getvalue = 0;

  ChlW2Grid g = NULL;

  /* g is null */
  assert_negative (chl_w2_grid_get (g, 5, 2, &getvalue));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_negative (chl_w2_grid_set (g, 5, 2, setvalue));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  g = chl_w2_grid_new (n_segments, n_layers, 0, 0, 0, 0);

  /* invalid segment number */
  assert_negative (chl_w2_grid_get (g, 0, 2, &getvalue));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_negative (chl_w2_grid_set (g, 0, 2, getvalue));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_negative (chl_w2_grid_get (g, n_segments + 1, 2, &getvalue));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_negative (chl_w2_grid_set (g, n_segments + 1, 2, getvalue));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  /* invalid layer number */
  assert_negative (chl_w2_grid_get (g, 5, 0, &getvalue));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_negative (chl_w2_grid_set (g, 5, 0, setvalue));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_negative (chl_w2_grid_get (g, 5, n_layers + 1, &getvalue));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_negative (chl_w2_grid_set (g, 5, n_layers + 1, setvalue));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  real min   = -1e5;
  real max   = 1e5;
  real range = max - min;

  srand (time (0));

  for (int i = 1; i <= n_segments; i++)
    {
      for (int j = 1; j <= n_layers; j++)
        {
          setvalue = max - (real) rand () / (float) (RAND_MAX / range);
          if (chl_w2_grid_set (g, i, j, setvalue) < 0)
            {
              chl_err_stack_print ();
              return EXIT_FAILURE;
            }
          if (chl_w2_grid_get (g, i, j, &getvalue) < 0)
            {
              chl_err_stack_print ();
              return EXIT_FAILURE;
            }

          assert_equal (setvalue, getvalue);
        }
    }

  chl_w2_grid_free (g);

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
