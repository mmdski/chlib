#include <chl/chl_error.h>
#include <chl/chl_reach.h>

#include "chltest.h"

void
test_new (void)
{
  size_t n_nodes = 10;

  ChlReach reach = chl_reach_new (n_nodes);
  assert_nonnull (reach);

  chl_reach_free (reach);
  reach = NULL;

  reach = chl_reach_new (0);
  assert_nonnull (reach);
  chl_reach_free (reach);
}

void
test_free (void)
{
  size_t n_nodes = 10;

  ChlReach reach = chl_reach_new (n_nodes);
  assert_nonnull (reach);

  chl_reach_free (reach);
  reach = NULL;

  chl_reach_free (reach);
  assert_null (reach);
}

void
test_thalweg (void)
{
  size_t n_nodes = 10;

  ChlReach reach = chl_reach_new (n_nodes);

  double reach_length = 100;
  double bed_slope    = 0.001;
  double bed_height   = reach_length * bed_slope;

  double dx     = reach_length / (double) n_nodes;
  double dy     = bed_height / (double) n_nodes;
  double x_dist = 0;

  double *thalweg_check = calloc (reach->n_nodes, sizeof (double));

  for (size_t i = 0; i < n_nodes; i++)
    {
      if (chl_reach_set_sta (reach, i, NULL, NULL, bed_height, x_dist) < 0)
        {
          chl_err_stack_print (__FILE__, __LINE__);
          chl_exit (EXIT_FAILURE);
        }
      thalweg_check[i] = bed_height;
      x_dist += dx;
      bed_height -= dy;
    }

  double *thalweg = calloc ((reach->n_nodes), sizeof (double));
  if (chl_reach_thalweg (reach, &thalweg) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      chl_exit (EXIT_FAILURE);
    }

  for (size_t i = 0; i < n_nodes; i++)
    {
      assert_equal (thalweg_check[i], thalweg[i]);
    }

  chl_reach_free (reach);
  free (thalweg_check);
  free (thalweg);
}

void
test_set_sta (void)
{
  size_t n_nodes = 1;

  ChlReach reach = chl_reach_new (n_nodes);
  assert_nonnull (reach);

  if (chl_reach_set_sta (reach, 0, NULL, NULL, 0, 0) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      chl_exit (EXIT_FAILURE);
    }

#ifdef CHECK_ARGS
  assert_negative (chl_reach_set_sta (NULL, 0, NULL, NULL, 0, 0));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_negative (chl_reach_set_sta (reach, 1, NULL, NULL, 0, 0));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();
#endif

  chl_reach_free (reach);
}

void
test_get_sta (void)
{
  size_t   n_nodes = 1;
  ChlReach reach   = chl_reach_new (n_nodes);
  assert_nonnull (reach);

  double xs = 20;
  if (chl_reach_set_sta (reach, 0, &xs, NULL, 0, 0) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      chl_exit (EXIT_FAILURE);
    }

  double *xs_p = chl_reach_get_sta (reach, 0);
  assert_nonnull (xs_p);

  assert_equal (xs, *xs_p);
  assert_equal (&xs, xs_p);

#ifdef CHECK_ARGS
  assert_null (chl_reach_get_sta (NULL, 0));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_null (chl_reach_get_sta (reach, 1));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();
#endif

  chl_reach_free (reach);
}

int
test_xsp_func (void *xs, double y, ChlXSProps *xsp_ptr)
{
  if (*xsp_ptr == NULL)
    {
      *xsp_ptr = chl_xs_props_new ();
    }

  ChlXSProps xsp = *xsp_ptr;

  chl_xs_props_set (xsp, XS_DEPTH, y);
  return 0;
}

int
test_xsp_func_fail (void *xs, double y, ChlXSProps *xsp_ptr)
{
  return -1;
}

void
test_get_xsp (void)
{
  size_t   n_nodes = 10;
  ChlReach reach   = chl_reach_new (n_nodes);

  double elev_datum = 10;

  if (chl_reach_set_sta (reach, 0, NULL, test_xsp_func, elev_datum, 0) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      chl_exit (EXIT_FAILURE);
    }

  if (chl_reach_set_sta (reach, 1, NULL, test_xsp_func_fail, 0, 0) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      chl_exit (EXIT_FAILURE);
    }

  double     elev = 20;
  ChlXSProps xsp  = NULL;

  if (chl_reach_get_xsp (reach, 0, elev, &xsp) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      chl_exit (EXIT_FAILURE);
    }
  assert_nonnull (xsp);

  double xs_depth;
  if (chl_xs_props_get (xsp, XS_DEPTH, &xs_depth) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      chl_exit (EXIT_FAILURE);
    }
  assert_equal (xs_depth, (elev - elev_datum));

  assert_negative (chl_reach_get_xsp (reach, 1, elev, &xsp));
  chl_err_stack_clear ();

  chl_xs_props_free (xsp);
  chl_reach_free (reach);
}

int
main (void)
{
  RUN_TEST_FUNC (test_new)
  RUN_TEST_FUNC (test_free)
  RUN_TEST_FUNC (test_thalweg)
  RUN_TEST_FUNC (test_set_sta)
  RUN_TEST_FUNC (test_get_sta)
  RUN_TEST_FUNC (test_get_xsp)

  EXIT_TEST
}
