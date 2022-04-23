#include <chl.h>
#include <math.h>
#include <stdlib.h>

const real WIDTH = 1;

int  n         = 5;
real z[]       = { 0, 0, 0.5, 1, 1 };
real y[]       = { 1, 0, 0, 0, 1 };
real roughness = 0.035;

ChlXSCompound
new_rect_xs ()
{
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

#ifdef REAL_IS_FLOAT
  return kc / roughness * powf (hr, 2. / 3.) * area;
#else
  return kc / roughness * pow (hr, 2. / 3.) * area;
#endif
}
