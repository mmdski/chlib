#include "properties.h"
#include "memory.h"
#include <assert.h>

struct ChlXSProps
{
  real *properties;
};

ChlXSProps
xsp_new (void)
{
  ChlXSProps xsp;
  NEW (xsp);
  xsp->properties = chl_calloc (N_XSP, sizeof (real));
  return xsp;
}

void
chl_xs_props_free (ChlXSProps xsp)
{
  assert (xsp);
  chl_free (xsp->properties);
  FREE (xsp);
}

real
chl_xs_props_get (ChlXSProps xsp, ChlXSPropType prop)
{
  assert (xsp);
  return *(xsp->properties + prop);
}

void
xsp_set (ChlXSProps xsp, ChlXSPropType prop, real value)
{
  assert (xsp);
  *(xsp->properties + prop) = value;
}
