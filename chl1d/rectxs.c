#include <stdlib.h>

#include <chl/chl1d.h>
#include <chl/chlerror.h>

#include "error.h"
#include "memory.h"

struct Chl1DRectXS
{
  real width;
};

// creates a new rectangular cross section
Chl1DRectXS
chl_1d_rectxs_new (real width)
{
  if (width <= 0)
    RAISE_ARG_ERR_NULL;

  Chl1DRectXS xs;
  NEW (xs);

  xs->width = width;

  return xs;
}

// frees a rectangular cross section
int
chl_1d_rectxs_free (Chl1DRectXS xs)
{
  if (xs == NULL)
    RAISE_NULL_ERR_INT;

  FREE (xs);

  return 0;
}

// returns the area
int
chl_1d_rectxs_area (Chl1DRectXS xs, real y, real *area)
{
  if (xs == NULL)
    RAISE_NULL_ERR_INT;

  *area = xs->width * y;

  return 0;
}

// wetted perimeter
int
chl_1d_rectxs_wp (Chl1DRectXS xs, real y, real *wp)
{
  if (xs == NULL)
    RAISE_NULL_ERR_INT;

  *wp = 2 * y + xs->width;

  return 0;
}

int
chl_1d_rectxs_tw (Chl1DRectXS xs, real y, real *tw)
{
  if (xs == NULL)
    RAISE_NULL_ERR_INT;

  *tw = xs->width;

  return 0;
}

int
chl_1d_rectxs_hr (Chl1DRectXS xs, real y, real *hr)
{
  if (xs == NULL)
    RAISE_NULL_ERR_INT;

  *hr = (y * xs->width) / (2 * y + xs->width);

  return 0;
}
