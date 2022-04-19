#include <chl.h>

static real gravity            = 9.81;
static real manning_conversion = 1;

real
chl_const_gravity (void)
{
  return gravity;
}

real
chl_const_manning (void)
{
  return manning_conversion;
}

void
chl_const_set_gravity (real g)
{
  gravity = g;
}

void
chl_const_set_manning (real k)
{
  manning_conversion = k;
}
