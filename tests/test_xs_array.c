#include <chl/chl_xs.h>

#include "chltest.h"

void
test_new (void)
{
  int    n   = 4;
  double y[] = { 1, 0, 0, 1 };
  double z[] = { 0, 0, 1, 1 };

  ChlXSArray a = chl_xs_array_new (n, y, z);
  assert_nonnull (a);
  assert_false (chl_err_stack_is_err ());
  chl_xs_array_free (a);

  ChlXSArray b;
  b = chl_xs_array_new (n, NULL, z);
  assert_null (b);
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  b = chl_xs_array_new (n, y, NULL);
  assert_null (b);
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  // test non-ascending z
  b = chl_xs_array_new (n, y, y);
  assert_null (b);
  assert_true (chl_err_stack_is_type (VALUE_ERROR));
  chl_err_stack_clear ();
}

void
test_free (void)
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
}

void
test_eq (void)
{
  int n1 = 4;
  int n2 = 4;
  int n3 = 5;

  double y1[] = { 1, 0, 0, 1 };
  double z1[] = { 0, 0, 1, 1 };

  double y2[] = { 1, 2, 0, 1 };
  double z2[] = { -1, 0, 1, 1 };

  double y3[] = { 1, 0, 0, 0, 1 };
  double z3[] = { 0, 0, 1, 1, 1 };

  ChlXSArray a1 = chl_xs_array_new (n1, y1, z1);
  assert_nonnull (a1);

  ChlXSArray a2 = chl_xs_array_new (n2, y2, z2);
  assert_nonnull (a2);

  ChlXSArray a3 = chl_xs_array_new (n3, y3, z3);
  assert_nonnull (a3);

  ChlXSArray a4 = chl_xs_array_new (n1, y1, z1);
  assert_nonnull (a4);

  assert_false (chl_xs_array_eq (NULL, NULL));
  assert_false (chl_xs_array_eq (NULL, a1));
  assert_false (chl_xs_array_eq (a1, NULL));

  assert_true (chl_xs_array_eq (a1, a1));
  assert_true (chl_xs_array_eq (a1, a4));
  assert_true (chl_xs_array_eq (a4, a1));

  assert_false (chl_xs_array_eq (a1, a2));
  assert_false (chl_xs_array_eq (a2, a1));

  assert_false (chl_xs_array_eq (a1, a3));
  assert_false (chl_xs_array_eq (a3, a1));

  chl_xs_array_free (a1);
  chl_xs_array_free (a2);
  chl_xs_array_free (a3);
  chl_xs_array_free (a4);
}

void
test_copy (void)
{
  int    n1   = 4;
  double y1[] = { 1, 0, 0, 1 };
  double z1[] = { 0, 0, 1, 1 };

  ChlXSArray a1 = chl_xs_array_new (n1, y1, z1);
  assert_nonnull (a1);

  ChlXSArray a2 = chl_xs_array_copy (a1);
  assert_nonnull (a2);

  assert_true (chl_xs_array_eq (a1, a2));

  assert_null (chl_xs_array_copy (NULL));
  assert_true (chl_err_stack_is_err ());
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  chl_xs_array_free (a1);
  chl_xs_array_free (a2);
}

void
test_vals (void)
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
}

void
test_subarray (void)
{
  int        n   = 8;
  double     z[] = { 0, 0, 0.33, 0.33, 0.66, 0.66, 1, 1 };
  double     y[] = { 1, 0.5, 0.5, 0, 0, 0.5, 0.5, 1 };
  ChlXSArray a   = chl_xs_array_new (n, y, z);

  int        n1   = 3;
  double     z1[] = { 0, 0, 0.33 };
  double     y1[] = { 1, 0.5, 0.5 };
  ChlXSArray a1   = chl_xs_array_new (n1, y1, z1);

  ChlXSArray a1_sub = chl_xs_array_subarray (a, 0, 0.33);

  int     len       = chl_xs_array_length (a1_sub);
  double *elevation = calloc (len, sizeof (double));
  double *station   = calloc (len, sizeof (double));
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
  double     z2[] = { 0.66, 1, 1 };
  double     y2[] = { 0.5, 0.5, 1 };
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
}

int
main (void)
{
  RUN_TEST_FUNC (test_new)
  RUN_TEST_FUNC (test_free)
  RUN_TEST_FUNC (test_eq)
  RUN_TEST_FUNC (test_copy)
  RUN_TEST_FUNC (test_vals)
  RUN_TEST_FUNC (test_subarray)

  EXIT_TEST
}
