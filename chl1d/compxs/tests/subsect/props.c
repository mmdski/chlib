#include <chl/chlerror.h>
#include <chl/chlmath.h>

#include "subsection.h"
#include "test.h"

#include "rectangle.c"

#define EPS 1e-5

void
test_rect (void)
{
  ChlXSSubsect rect_ss = new_rect_subsect ();
  Chl1DXSProps xsp;

  real min_h    = 0;
  real max_h    = 1;
  int  n_values = 10;
  real dh       = (max_h - min_h) / n_values;
  real h;
  real area;
  real tw;
  real wp;
  real hr;
  real k;

  for (int i = 0; i < 10; i++)
    {
      h = i * dh;

      xsp = chl_xs_subsect_props (rect_ss, h);
      assert_nonnull (xsp);

      assert_zero (chl_1d_xs_props_get (xsp, XS_AREA, &area));
      assert_approx_eq (area, rect_area (h), EPS);

      assert_zero (chl_1d_xs_props_get (xsp, XS_TOP_WIDTH, &tw));
      if (h <= 0)
        {
          assert_equal (tw, 0);
        }
      else
        {
          assert_approx_eq (tw, rect_tw (h), EPS);
        }

      assert_zero (chl_1d_xs_props_get (xsp, XS_WETTED_PERIMETER, &wp));
      if (h <= 0)
        {
          assert_equal (wp, 0);
        }
      else
        {
          assert_approx_eq (wp, rect_wp (h), EPS);
        }

      assert_zero (chl_1d_xs_props_get (xsp, XS_HYDRAULIC_RADIUS, &hr));
      if (h <= 0)
        {
          assert_true (isnan (hr));
        }
      else
        {
          assert_approx_eq (hr, rect_hr (h), EPS);
        }

      assert_zero (chl_1d_xs_props_get (xsp, XS_CONVEYANCE, &k));
      if (h <= 0)
        {
          assert_true (isnan (hr));
        }
      else
        {
          assert_approx_eq (k, rect_k (h), EPS);
        }

      chl_1d_xs_props_free (xsp);
    }

  chl_xs_subsect_free (rect_ss);
}

int
main (void)
{
  test_rect ();

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
