#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "error.h"
#include "memory.h"

struct ChlXSRect
{
  double width;
};

// creates a new rectangular cross section
ChlXSRect
chl_xs_rect_new (double width)
{

#ifdef CHECK_ARGS
  if (width <= 0)
    RAISE_ARG_ERR_NULL;
#endif

  ChlXSRect xs;
  NEW (xs);

  xs->width = width;

  return xs;
}

// frees a rectangular cross section
int
chl_xs_rect_free (ChlXSRect xs)
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
chl_xs_rect_area (ChlXSRect xs, double y, double *area)
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
chl_xs_rect_wp (ChlXSRect xs, double y, double *wp)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  *wp = 2 * y + xs->width;

  return 0;
}

int
chl_xs_rect_tw (ChlXSRect xs, double y, double *tw)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  *tw = xs->width;

  return 0;
}

int
chl_xs_rect_hr (ChlXSRect xs, double y, double *hr)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  *hr = (y * xs->width) / (2 * y + xs->width);

  return 0;
}
