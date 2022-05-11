#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "chlassert.h"

#include "xs_subsect_rect.c"

#define EPS 1e-5

void
test_rect (void)
{
  ChlXSSubsect rect_ss = new_rect_subsect ();
  ChlXSProps   xsp     = NULL;

  double min_h    = 0;
  double max_h    = 1;
  int    n_values = 10;
  double dh       = (max_h - min_h) / n_values;
  double h;
  double area;
  double tw;
  double wp;
  double hr;
  double k;

  for (int i = 0; i < 10; i++)
    {
      h = i * dh;

      assert_zero (chl_xs_subsect_props (rect_ss, h, &xsp));
      assert_nonnull (xsp);

      assert_zero (chl_xs_props_get (xsp, XS_AREA, &area));
      assert_approx_eq (area, rect_area (h), EPS);

      assert_zero (chl_xs_props_get (xsp, XS_TOP_WIDTH, &tw));
      if (h <= 0)
        {
          assert_equal (tw, 0);
        }
      else
        {
          assert_approx_eq (tw, rect_tw (h), EPS);
        }

      assert_zero (chl_xs_props_get (xsp, XS_WETTED_PERIMETER, &wp));
      if (h <= 0)
        {
          assert_equal (wp, 0);
        }
      else
        {
          assert_approx_eq (wp, rect_wp (h), EPS);
        }

      assert_zero (chl_xs_props_get (xsp, XS_HYDRAULIC_RADIUS, &hr));
      if (h <= 0)
        {
          assert_true (isnan (hr));
        }
      else
        {
          assert_approx_eq (hr, rect_hr (h), EPS);
        }

      assert_zero (chl_xs_props_get (xsp, XS_CONVEYANCE, &k));
      if (h <= 0)
        {
          assert_true (isnan (hr));
        }
      else
        {
          assert_approx_eq (k, rect_k (h), EPS);
        }
    }

  chl_xs_props_free (xsp);
  chl_xs_subsect_free (rect_ss);
}

int
main (void)
{
  test_rect ();

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
