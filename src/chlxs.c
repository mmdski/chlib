#include "chlmem.h"
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
    return NULL;

  ChlXSRect xs;
  NEW (xs);

  if (xs == 0)
    abort ();

  xs->width = width;

  return xs;
}

// frees a rectangular cross section
int
chl_xs_rect_free (ChlXSRect xs)
{
  if (xs == NULL)
    return -1;

  FREE (xs);

  return 0;
}
