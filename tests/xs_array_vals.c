#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "chlassert.h"

int
main (void)
{
  int        n   = 8;
  double     z[] = { 0, 0, 0.33, 0.33, 0.66, 0.66, 1, 1 };
  double     y[] = { 1, 0.5, 0.5, 0, 0, 0.5, 0.5, 1 };
  ChlXSArray a   = chl_xs_array_new (n, y, z);

  int     len       = chl_xs_array_length (a);
  double *station   = calloc (len, sizeof (double));
  double *elevation = calloc (len, sizeof (double));

  assert_positive (chl_xs_array_vals (a, elevation, station));

  for (int i = 0; i < len; i++)
    {
      assert_equal (z[i], elevation[i]);
      assert_equal (y[i], station[i]);
    }

  free (elevation);
  free (station);
  chl_xs_array_free (a);

  assert_negative (chl_xs_array_vals (NULL, elevation, station));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
