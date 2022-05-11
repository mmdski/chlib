#include <assert.h>

#include <chl/chl_error.h>

#include "error.h"
#include "memory.h"
#include "xs_properties.h"

struct ChlXSProps
{
  double *properties;
};

ChlXSProps
xsp_new (void)
{
  ChlXSProps xsp;
  NEW (xsp);
  xsp->properties = chl_calloc (N_XSP, sizeof (double));
  return xsp;
}

void
chl_xs_props_free (ChlXSProps xsp)
{
  if (xsp)
    {
      chl_free (xsp->properties);
      FREE (xsp);
    }
}

int
chl_xs_props_get (ChlXSProps xsp, ChlXSPropNum prop, double *value)
{
  if (!xsp)
    RAISE_NULL_ERR_INT;

  *value = *(xsp->properties + prop);

  return 0;
}

void
xsp_set (ChlXSProps xsp, ChlXSPropNum prop, double value)
{
  assert (xsp);
  *(xsp->properties + prop) = value;
}
