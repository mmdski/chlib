#include "test.h"
#include <chl.h>

int
main ()
{
  real g = 10;
  chl_const_set_gravity (g);
  assert_equal (g, chl_const_gravity ());

  g = 20;
  chl_const_set_gravity (g);
  assert_equal (g, chl_const_gravity ());

  real k = 1.49;
  chl_const_set_manning (k);
  assert_equal (k, chl_const_manning ());

  k = 2;
  chl_const_set_manning (k);
  assert_equal (k, chl_const_manning ());

  return EXIT_SUCCESS;
}
