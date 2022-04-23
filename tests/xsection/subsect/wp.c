#include <chl.h>
#include <math.h>

#include "rectangle.c"
#include "test.h"

int
main ()
{
  ChlXSSubsect rect_ss = new_rect_subsect ();

  real min_y    = 0;
  real max_y    = 1;
  int  n_values = 10;
  real dy       = (max_y - min_y) / n_values;
  real y;
  real wp;
  real diff;

  for (int i = 0; i < 10; i++)
    {
      y = i * dy;
      assert_zero (chl_xs_subsect_wp (rect_ss, y, &wp));
      if (y == 0)
        {
          assert_equal (wp, 0);
        }
      else
        {
          diff = wp - rect_wp (y);
#if defined(REAL_IS_FLOAT)
          assert_true ((fabsf (diff) < 1e-5));
#else
          assert_true ((fabs (diff) < 1e-5));
#endif
        }
    }

  assert_negative (chl_xs_subsect_area (NULL, y, &wp));
  assert_true (chl_err_stack_is_err ());
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_negative (chl_xs_subsect_area (rect_ss, y, NULL));
  assert_true (chl_err_stack_is_err ());
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  chl_xs_subsect_free (rect_ss);

  return EXIT_SUCCESS;
}
