#include "chlmem.h"
#include <chl/chlerror.h>
#include <chl/chlxs.h>
#include <stdlib.h>

struct ChlXSRect
{
  real width;
};

// creates a new rectangular cross section
ChlXSRect
chl_xs_rect_new (real width)
{
  if (width <= 0)
    {
      chl_err_raise (
          INVALID_ARGUMENT_ERROR, "Invalid width", __FILE__, __LINE__);
      return NULL;
    }

  ChlXSRect xs;
  NEW (xs);

  if (xs == 0)
    {
      chl_err_raise (
          MEMORY_ERROR, "Unable to allocate memory", __FILE__, __LINE__);
      return NULL;
    }

  xs->width = width;

  return xs;
}

// frees a rectangular cross section
int
chl_xs_rect_free (ChlXSRect xs)
{
  if (xs == NULL)
    {
      chl_err_raise (NULL_ARGUMENT_ERROR, "", __FILE__, __LINE__);
      return -1;
    }

  FREE (xs);

  return 0;
}
