#include <math.h>
#include <stdlib.h>

#include <chl/chl_constants.h>
#include <chl/chl_xs.h>

#include "chlassert.h"

#define EPS 1e-5

#define WIDTH 1

ChlXSComp
new_rect_xs (void)
{
  int    n         = 5;
  double z[]       = { 0, 0, 0.5, 1, 1 };
  double y[]       = { 1, 0, 0, 0, 1 };
  double roughness = 0.035;

  ChlXSComp xs = chl_xs_comp_new (n, y, z, 1, &roughness, NULL);

  return xs;
}

double
rect_area (double y)
{
  return y * WIDTH;
}

double
rect_wp (double y)
{
  if (y <= 0)
    return 0;
  else
    return 2 * y + WIDTH;
}

double
rect_tw (double y)
{
  if (y <= 0)
    return 0;
  else
    return WIDTH;
}

double
rect_hd (double y)
{
  return rect_area (y) / rect_tw (y);
}

double
rect_hr (double y)
{
  return rect_area (y) / rect_wp (y);
}

double
rect_k (double y)
{
  double area = rect_area (y);
  double hr   = rect_hr (y);
  double kc   = chl_const_manning ();

  return kc / 0.035 * pow (hr, 2. / 3.) * area;
}

void
test_rect (void)
{
  ChlXSComp  xs = new_rect_xs ();
  ChlXSProps xsp;

  double min_h    = 0;
  double max_h    = 1;
  int    n_values = 10;
  double dh       = (max_h - min_h) / n_values;
  double h;
  double area;
  double tw;
  double wp;
  double hr;
  double hd;
  double k;
  double alpha;

  for (int i = 0; i < 10; i++)
    {
      h = i * dh;

      xsp = chl_xs_comp_props (xs, h);
      assert_nonnull (xsp);

      assert_zero (chl_xs_props_get (xsp, XS_AREA, &area));
      assert_approx_eq (area, rect_area (h), EPS);

      assert_zero (chl_xs_props_get (xsp, XS_TOP_WIDTH, &tw));
      assert_approx_eq (tw, rect_tw (h), EPS);

      assert_zero (chl_xs_props_get (xsp, XS_WETTED_PERIMETER, &wp));
      assert_approx_eq (wp, rect_wp (h), EPS);

      assert_zero (chl_xs_props_get (xsp, XS_HYDRAULIC_RADIUS, &hr));
      if (h <= 0)
        {
          assert_true (isnan (hr));
        }
      else
        {
          assert_approx_eq (hr, rect_hr (h), EPS);
        }

      assert_zero (chl_xs_props_get (xsp, XS_HYDRAULIC_DEPTH, &hd));
      if (h <= 0)
        {
          assert_true (isnan (hd));
        }
      else
        {
          assert_approx_eq (hd, rect_hd (h), EPS);
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

      assert_zero (chl_xs_props_get (xsp, XS_VELOCITY_COEFF, &alpha));
      if (h <= 0)
        {
          assert_true (isnan (alpha));
        }
      else
        {
          assert_approx_eq (alpha, 1, EPS);
        }

      chl_xs_props_free (xsp);
    }

  chl_xs_comp_free (xs);
}
