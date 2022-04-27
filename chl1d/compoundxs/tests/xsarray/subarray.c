#include <chl.h>
#include <stdio.h>
#include <stdlib.h>

#include "test.h"

int
main (void)
{
  int        n   = 8;
  real       z[] = { 0, 0, 0.33, 0.33, 0.66, 0.66, 1, 1 };
  real       y[] = { 1, 0.5, 0.5, 0, 0, 0.5, 0.5, 1 };
  ChlXSArray a   = chl_xs_array_new (n, y, z);

  int        n1   = 3;
  real       z1[] = { 0, 0, 0.33 };
  real       y1[] = { 1, 0.5, 0.5 };
  ChlXSArray a1   = chl_xs_array_new (n1, y1, z1);

  ChlXSArray a1_sub = chl_xs_array_subarray (a, 0, 0.33);

  int   len       = chl_xs_array_length (a1_sub);
  real *elevation = calloc (len, sizeof (real));
  real *station   = calloc (len, sizeof (real));
  chl_xs_array_vals (a1_sub, elevation, station);
  for (int i = 0; i < len; i++)
    {
      printf ("%i %f %f\n", i, elevation[i], station[i]);
    }

  free (elevation);
  free (station);

  assert_true (chl_xs_array_eq (a1, a1_sub));
  chl_xs_array_free (a1);
  chl_xs_array_free (a1_sub);

  int        n2   = 3;
  real       z2[] = { 0.66, 1, 1 };
  real       y2[] = { 0.5, 0.5, 1 };
  ChlXSArray a2   = chl_xs_array_new (n2, y2, z2);

  ChlXSArray a2_sub = chl_xs_array_subarray (a, 0.66, 1);
  printf ("len : %i\n", chl_xs_array_length (a2_sub));
  assert_true (chl_xs_array_eq (a2, a2_sub));
  chl_xs_array_free (a2);
  chl_xs_array_free (a2_sub);

  assert_null (chl_xs_array_subarray (NULL, 0, 1));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_null (chl_xs_array_subarray (a, -1, 1));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_null (chl_xs_array_subarray (a, 0, 2));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  chl_xs_array_free (a);

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
