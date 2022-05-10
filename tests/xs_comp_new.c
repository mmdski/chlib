#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "chlassert.h"

/* simple geometry single subsection */
void
test_simple_single (void)
{
  int    n         = 4;
  double z[]       = { 0, 0, 1, 1 };
  double y[]       = { 1, 0, 0, 1 };
  double roughness = 0.035;

  Chl1DCompXS xs = chl_xs_comp_new (n, y, z, 1, &roughness, NULL);
  assert_nonnull (xs);
  chl_xs_comp_free (xs);
}

/* simple geometry compound */
void
test_simple_comp (void)
{
  int    n             = 8;
  double z[]           = { 0, 0, 0.33, 0.33, 0.66, 0.66, 1, 1 };
  double y[]           = { 1, 0.5, 0.5, 0, 0, 0.5, 0.5, 1 };
  int    n_roughness   = 3;
  double roughness[]   = { 0.6, 0.35, 0.6 };
  double z_roughness[] = { 0.33, 0.66 };

  Chl1DCompXS xs =
      chl_xs_comp_new (n, y, z, n_roughness, roughness, z_roughness);
  assert_nonnull (xs);
  chl_xs_comp_free (xs);
}

int
main (void)
{
  test_simple_single ();
  test_simple_comp ();

  /* test errors */
  int    n             = 4;
  double z[]           = { 0, 0, 1, 1 };
  double y[]           = { 1, 0, 0, 1 };
  int    n_roughness   = 1;
  double roughness     = 0.035;
  double inv_roughness = -roughness;

  Chl1DCompXS xs;

  /* invalid number of coordinates */
  xs = chl_xs_comp_new (1, y, z, 1, &roughness, NULL);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  /* NULL y pointer */
  xs = chl_xs_comp_new (n, NULL, z, n_roughness, &roughness, NULL);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  /* NULL z pointer */
  xs = chl_xs_comp_new (n, y, NULL, n_roughness, &roughness, NULL);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  /* NULL y and z pointers */
  xs = chl_xs_comp_new (n, NULL, NULL, n_roughness, &roughness, NULL);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  /* invalid number of roughnesses */
  xs = chl_xs_comp_new (n, y, z, 0, &roughness, NULL);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  /* NULL roughness pointer */
  xs = chl_xs_comp_new (n, y, z, n_roughness, NULL, NULL);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  /* invalid roughness */
  xs = chl_xs_comp_new (n, y, z, n_roughness, &inv_roughness, NULL);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  /* NULL z_roughness pointer */
  xs = chl_xs_comp_new (n, y, z, 2, &roughness, NULL);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
