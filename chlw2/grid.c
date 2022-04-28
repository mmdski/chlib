#include <stdlib.h>

#include <chl/chlerror.h>
#include <chl/chlmath.h>
#include <chl/chlw2.h>

#include "error.h"
#include "memory.h"

struct ChlW2SGrid
{
  int    n_segments;
  int    n_layers;
  real **values;
};

ChlW2SGrid
chl_w2_sgrid_new (int n_segments, int n_layers)
{
  if (n_segments <= 0 || n_layers <= 0)
    RAISE_ARG_ERR_NULL;

  real **values = chl_calloc (n_segments, sizeof (real *));

  for (int i = 0; i < n_segments; i++)
    {
      *(values + i) = chl_calloc (n_layers, sizeof (real *));
    }

  ChlW2SGrid g;
  NEW (g);
  g->n_segments = n_segments;
  g->n_layers   = n_layers;
  g->values     = values;

  return g;
}

void
chl_w2_sgrid_free (ChlW2SGrid g)
{
  if (!g)
    return;

  int    n_segments = g->n_segments;
  real **values     = g->values;

  for (int i = 0; i < n_segments; i++)
    {
      chl_free (*(values + i));
    }

  chl_free (values);
  FREE (g);
}
