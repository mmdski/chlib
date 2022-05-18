#include <assert.h>

#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "error.h"
#include "memory.h"

#define FILENAME "xs_properties.c"

struct _ChlXSProps
{
  double *properties;
};

ChlXSProps
chl_xs_props_new (void)
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
chl_xs_props_set (ChlXSProps xsp, ChlXSPropNum prop, double value)
{
  assert (xsp);
  *(xsp->properties + prop) = value;
}
