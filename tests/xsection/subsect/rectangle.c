#include <chl.h>

const real WIDTH = 1;

ChlXSSubsect
new_rect_subsect ()
{
  int  n         = 5;
  real z[]       = { 0, 0, 0.5, 1, 1 };
  real y[]       = { 1, 0, 0, 0, 1 };
  real roughness = 0.035;

  ChlXSArray   a  = chl_xs_array_new (n, y, z);
  ChlXSSubsect ss = chl_xs_subsect_new (a, roughness);
  chl_xs_array_free (a);

  return ss;
}

real
rect_area (real y)
{
  return y * WIDTH;
}

real
rect_wp (real y)
{
  return 2 * y + WIDTH;
}
