#include <stdlib.h>

#include <chl/chl1d.h>
#include <chl/chlerror.h>

#include "error.h"
#include "memory.h"

struct Chl1DRectXS
{
  double width;
};

// creates a new rectangular cross section
Chl1DRectXS
chl_1d_rectxs_new (double width)
{

#ifdef CHECK_ARGS
  if (width <= 0)
    RAISE_ARG_ERR_NULL;
#endif

  Chl1DRectXS xs;
  NEW (xs);

  xs->width = width;

  return xs;
}

// frees a rectangular cross section
int
chl_1d_rectxs_free (Chl1DRectXS xs)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  FREE (xs);

  return 0;
}

// returns the area
int
chl_1d_rectxs_area (Chl1DRectXS xs, double y, double *area)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  *area = xs->width * y;

  return 0;
}

// wetted perimeter
int
chl_1d_rectxs_wp (Chl1DRectXS xs, double y, double *wp)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  *wp = 2 * y + xs->width;

  return 0;
}

int
chl_1d_rectxs_tw (Chl1DRectXS xs, double y, double *tw)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  *tw = xs->width;

  return 0;
}

int
chl_1d_rectxs_hr (Chl1DRectXS xs, double y, double *hr)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  *hr = (y * xs->width) / (2 * y + xs->width);

  return 0;
}
