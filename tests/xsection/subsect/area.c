#include "../rectangle.h"
#include "test.h"

int
main ()
{
  ChlXSSubsect rect_ss = new_rect_subsect ();

  real min_y    = 0;
  real max_y    = 10;
  int  n_values = 10;
  real dy       = (max_y - min_y) / n_values;
  real y;
  real area;

  for (int i = 0; i < 10; i++)
    {
      y = i * dy;
      assert_zero (chl_xs_subsect_area (rect_ss, y, &area));
      assert_equal (area, rect_area (y));
    }

  chl_xs_subsect_free (rect_ss);

  return EXIT_SUCCESS;
}
