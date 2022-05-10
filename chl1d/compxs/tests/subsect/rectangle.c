#include <math.h>

#include <chl/chlconstants.h>

#include "subsection.h"

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
