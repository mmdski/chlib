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
xsp_free (ChlXSProps xsp)
{
  assert (xsp);
  chl_free (xsp->properties);
  FREE (xsp);
}

real
xsp_get (ChlXSProps xsp, xs_prop prop)
{
  assert (xsp);
  return *(xsp->properties + prop);
}

void
xsp_set (ChlXSProps xsp, xs_prop prop, real value)
{
  assert (xsp);
  *(xsp->properties + prop) = value;
}
