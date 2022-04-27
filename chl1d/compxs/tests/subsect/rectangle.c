#include <math.h>

#include <chl/chlconstants.h>

#include "subsection.h"

const real WIDTH = 1;

ChlXSSubsect
new_rect_subsect (void)
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

real
rect_tw (real y)
{
  return WIDTH;
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
