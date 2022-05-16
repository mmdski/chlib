#include <math.h>

#include <chl/chl_constants.h>
#include <chl/chl_xs.h>

#include "chltest.h"

#define EPS 1e-5

const double WIDTH = 1;

ChlXSSubsect
new_rect_subsect (void)
{
  int    n         = 5;
  double z[]       = { 0, 0, 0.5, 1, 1 };
  double y[]       = { 1, 0, 0, 0, 1 };
  double roughness = 0.035;

  ChlXSArray   a  = chl_xs_array_new (n, y, z);
  ChlXSSubsect ss = chl_xs_subsect_new (a, roughness);
  chl_xs_array_free (a);

  return ss;
}

double
rect_area (double y)
{
  return y * WIDTH;
}

double
rect_wp (double y)
{
  return 2 * y + WIDTH;
}

double
rect_tw (double y)
{
  return WIDTH;
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
test_new (void)
{
  int    n   = 4;
  double y[] = { 1, 0, 0, 1 };
  double z[] = { 0, 0, 1, 1 };

  ChlXSArray a = chl_xs_array_new (n, y, z);
  assert_nonnull (a);

  double       roughness = 0.035;
  ChlXSSubsect ss        = chl_xs_subsect_new (a, roughness);
  assert_nonnull (ss);
  assert_zero (chl_xs_subsect_free (ss));

  ss = chl_xs_subsect_new (NULL, roughness);
  assert_null (ss);
  assert_true (chl_err_stack_is_err ());
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  ss = chl_xs_subsect_new (a, -roughness);
  assert_null (ss);
  assert_true (chl_err_stack_is_err ());
  assert_true (chl_err_stack_is_type (VALUE_ERROR));
  chl_err_stack_clear ();

  chl_xs_array_free (a);
}

void
test_free (void)
{
  int    n   = 4;
  double y[] = { 1, 0, 0, 1 };
  double z[] = { 0, 0, 1, 1 };

  ChlXSArray a = chl_xs_array_new (n, y, z);
  assert_nonnull (a);

  double       roughness = 0.035;
  ChlXSSubsect ss        = chl_xs_subsect_new (a, roughness);
  assert_nonnull (ss);
  assert_zero (chl_xs_subsect_free (ss));

  ss = NULL;
  assert_negative (chl_xs_subsect_free (ss));
  assert_true (chl_err_stack_is_err ());
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  chl_xs_array_free (a);
}

void
test_props_rect (void)
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

void
test_rough (void)
{
  int    n   = 4;
  double y[] = { 1, 0, 0, 1 };
  double z[] = { 0, 0, 1, 1 };

  ChlXSArray a = chl_xs_array_new (n, y, z);
  assert_nonnull (a);

  double       roughness = 0.035;
  ChlXSSubsect ss        = chl_xs_subsect_new (a, roughness);
  assert_nonnull (ss);
  chl_xs_array_free (a);

  double n_value;
  assert_zero (chl_xs_subsect_roughness (ss, &n_value));
  assert_equal (roughness, n_value);

  chl_xs_subsect_free (ss);
}

int
main (void)
{
  RUN_TEST_FUNC (test_new)

  // for some reason it's important to node that test_props_rect() runs before
  // test_free()
  RUN_TEST_FUNC (test_props_rect)
  RUN_TEST_FUNC (test_free)

  RUN_TEST_FUNC (test_rough)

  EXIT_TEST
}
