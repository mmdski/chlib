#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <chl/chl1d.h>
#include <chl/chlconstants.h>

#include "test.h"

#define EPS 1e-5

#define CHAN_WIDTH 0.33
#define FP_WIDTH 0.67

Chl1DCompXS
new_comprect_xs (void)
{
  int  n             = 8;
  real z[]           = { 0, 0, 0.33, 0.33, 0.66, 0.66, 1, 1 };
  real y[]           = { 1, 0.5, 0.5, 0, 0, 0.5, 0.5, 1 };
  int  n_roughness   = 3;
  real roughness[]   = { 0.06, 0.035, 0.06 };
  real z_roughness[] = { 0.33, 0.66 };

  Chl1DCompXS xs =
      chl_1d_compxs_new (n, y, z, n_roughness, roughness, z_roughness);

  return xs;
}

real
comprect_area (real y)
{
  if (y <= 0)
    return 0;
  else if (y < 0.5)
    return y * CHAN_WIDTH;
  else
    return (y - 0.5) * FP_WIDTH + y * CHAN_WIDTH;
}

real
comprect_wp (real y)
{
  if (y <= 0)
    return 0;
  else if (y <= 0.5)
    return 2 * y + CHAN_WIDTH;
  else
    return 2 * (y - 0.5) + FP_WIDTH + 2 * 0.5 + CHAN_WIDTH;
}

real
comprect_tw (real y)
{
  if (y <= 0)
    return 0;
  else if (y <= 0.5)
    return CHAN_WIDTH;
  else
    return 1;
}

real
comprect_hd (real y)
{
  return comprect_area (y) / comprect_tw (y);
}

real
comprect_hr (real y)
{
  return comprect_area (y) / comprect_wp (y);
}

real
comprect_k (real y)
{
  real a1, a2, a3;
  real wp1, wp2, wp3;
  real hr1, hr2, hr3;
  real k1, k2, k3;
  real kc = chl_const_manning ();

  if (y <= 0)
    {
      k1 = NAN;
      k2 = NAN;
      k3 = NAN;
    }
  else if (y < 0.5)
    {
      k1 = 0;
      k3 = 0;

      a2  = y * CHAN_WIDTH;
      wp2 = 2 * y + CHAN_WIDTH;
      hr2 = a2 / wp2;
      k2  = kc / 0.035 * a2 * chl_pow (hr2, 2. / 3.);
    }
  else
    {
      real y_ob = y - 0.5;

      a1  = y_ob * FP_WIDTH / 2;
      wp1 = y_ob + FP_WIDTH / 2;
      hr1 = a1 / wp1;
      k1  = kc / 0.06 * a1 * chl_pow (hr1, 2. / 3.);

      a2  = y * CHAN_WIDTH;
      wp2 = 2 * 0.5 + CHAN_WIDTH;
      hr2 = a2 / wp2;
      k2  = kc / 0.035 * a2 * chl_pow (hr2, 2. / 3.);

      a3  = y_ob * FP_WIDTH / 2;
      wp3 = y_ob + FP_WIDTH / 2;
      hr3 = a3 / wp3;
      k3  = kc / 0.06 * a3 * chl_pow (hr3, 2. / 3.);
    }

  return k1 + k2 + k3;
}

void
test_comprect (void)
{
  Chl1DCompXS  xs = new_comprect_xs ();
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
  real hd;
  real k;

  for (int i = 0; i < 10; i++)
    {
      h = i * dh;

      printf ("h = %f\n", h);

      xsp = chl_1d_compxs_props (xs, h);
      assert_nonnull (xsp);

      assert_zero (chl_1d_xs_props_get (xsp, XS_AREA, &area));
      printf ("a  : %f %f\n", area, comprect_area (h));
      assert_approx_eq (area, comprect_area (h), EPS);

      assert_zero (chl_1d_xs_props_get (xsp, XS_TOP_WIDTH, &tw));
      printf ("tw : %f %f\n", tw, comprect_tw (h));
      assert_approx_eq (tw, comprect_tw (h), EPS);

      assert_zero (chl_1d_xs_props_get (xsp, XS_WETTED_PERIMETER, &wp));
      printf ("wp : %f %f\n", wp, comprect_wp (h));
      assert_approx_eq (wp, comprect_wp (h), EPS);

      assert_zero (chl_1d_xs_props_get (xsp, XS_HYDRAULIC_RADIUS, &hr));
      printf ("hr : %f %f\n", hr, comprect_hr (h));
      if (h <= 0)
        {
          assert_true (isnan (hr));
        }
      else
        {
          assert_approx_eq (hr, comprect_hr (h), EPS);
        }

      assert_zero (chl_1d_xs_props_get (xsp, XS_HYDRAULIC_DEPTH, &hd));
      printf ("hd : %f %f\n", hd, comprect_hd (h));
      if (h <= 0)
        {
          assert_true (isnan (hd));
        }
      else
        {
          assert_approx_eq (hd, comprect_hd (h), EPS);
        }

      assert_zero (chl_1d_xs_props_get (xsp, XS_CONVEYANCE, &k));
      printf ("k  : %f %f\n", k, comprect_k (h));
      if (h <= 0)
        {
          assert_true (isnan (hr));
        }
      else
        {
          /* relative error for K */
          assert_approx_eq (k / comprect_k (h), 1, 1e-4);
        }

      printf ("\n");

      chl_1d_xs_props_free (xsp);
    }

  chl_1d_compxs_free (xs);
}
