#include <assert.h>

#include <chl/chlerror.h>

#include "error.h"
#include "memory.h"
#include "properties.h"

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
  if (xsp)
    {
      chl_free (xsp->properties);
      FREE (xsp);
    }
}

int
chl_xs_props_get (ChlXSProps xsp, ChlXSPropType prop, real *value)
{
  if (!xsp)
    RAISE_NULL_ERR_INT;

  *value = *(xsp->properties + prop);

  return 0;
}

void
xsp_set (ChlXSProps xsp, ChlXSPropType prop, real value)
{
  assert (xsp);
  *(xsp->properties + prop) = value;
}
