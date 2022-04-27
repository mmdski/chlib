#include <chl.h>
#include <math.h>
#include <stdlib.h>

#include "test.h"

#define EPS 1e-5

#define WIDTH 1

ChlXSCompound
new_rect_xs (void)
{
  int  n         = 5;
  real z[]       = { 0, 0, 0.5, 1, 1 };
  real y[]       = { 1, 0, 0, 0, 1 };
  real roughness = 0.035;

  ChlXSCompound xs = chl_xs_comp_new (n, y, z, 1, &roughness, NULL);

  return xs;
}

real
rect_area (real y)
{
  return y * WIDTH;
}

real
rect_wp (real y)
{
  if (y <= 0)
    return 0;
  else
    return 2 * y + WIDTH;
}

real
rect_tw (real y)
{
  if (y <= 0)
    return 0;
  else
    return WIDTH;
}

real
rect_hd (real y)
{
  return rect_area (y) / rect_tw (y);
}

real
rect_hr (real y)
{
  return rect_area (y) / rect_wp (y);
}

real
rect_k (real y)
{
  real area = rect_area (y);
  real hr   = rect_hr (y);
  real kc   = chl_const_manning ();

  return kc / 0.035 * chl_pow (hr, 2. / 3.) * area;
}

void
test_rect (void)
{
  ChlXSCompound xs = new_rect_xs ();
  ChlXSProps    xsp;

  real min_h    = 0;
  real max_h    = 1;
  int  n_values = 10;
  real dh       = (max_h - min_h) / n_values;
  real h;
  real area;
  real tw;
  real wp;
  real hr;
  real hd;
  real k;
  real alpha;

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
