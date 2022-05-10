#include <assert.h>

#include <chl/chlerror.h>

#include "error.h"
#include "memory.h"
#include "properties.h"

struct Chl1DXSProps
{
  double *properties;
};

Chl1DXSProps
xsp_new (void)
{
  Chl1DXSProps xsp;
  NEW (xsp);
  xsp->properties = chl_calloc (N_XSP, sizeof (double));
  return xsp;
}

void
chl_1d_xs_props_free (Chl1DXSProps xsp)
{
  if (xsp)
    {
      chl_free (xsp->properties);
      FREE (xsp);
    }
}

int
chl_1d_xs_props_get (Chl1DXSProps xsp, Chl1DXSPropNum prop, double *value)
{
  if (!xsp)
    RAISE_NULL_ERR_INT;

  *value = *(xsp->properties + prop);

  return 0;
}

void
xsp_set (Chl1DXSProps xsp, Chl1DXSPropNum prop, double value)
{
  assert (xsp);
  *(xsp->properties + prop) = value;
}
