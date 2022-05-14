#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_reach.h>
#include <chl/chl_xs.h>

#include "chlassert.h"

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

int
main (void)
{
  size_t   n_nodes = 10;
  ChlReach reach   = chl_reach_new (n_nodes);

  double elev_datum = 10;

  if (chl_reach_set_sta (reach, 0, NULL, test_xsp_func, elev_datum, 0) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      return EXIT_FAILURE;
    }

  if (chl_reach_set_sta (reach, 1, NULL, test_xsp_func_fail, 0, 0) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      return EXIT_FAILURE;
    }

  double     elev = 20;
  ChlXSProps xsp  = NULL;

  if (chl_reach_get_xsp (reach, 0, elev, &xsp) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      return EXIT_FAILURE;
    }
  assert_nonnull (xsp);

  double xs_depth;
  if (chl_xs_props_get (xsp, XS_DEPTH, &xs_depth) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      return EXIT_FAILURE;
    }
  assert_equal (xs_depth, (elev - elev_datum));

  assert_negative (chl_reach_get_xsp (reach, 1, elev, &xsp));
  chl_err_stack_clear ();

  chl_xs_props_free (xsp);
  chl_reach_free (reach);

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
