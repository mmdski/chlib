#include <stdlib.h>

#include <chl/chlerror.h>
#include <chl/chlmath.h>
#include <chl/chlw2.h>

#include "error.h"
#include "memory.h"

struct ChlW2Grid
{
  int    n_segments;
  int    n_layers;
  int    n_us;
  int    n_ds;
  int    n_top;
  int    n_bot;
  real **values;
};

ChlW2Grid
chl_w2_grid_new (
    int n_segments, int n_layers, int n_us, int n_ds, int n_top, int n_bot)
{
  if (n_segments <= 0 || n_layers <= 0)
    RAISE_ARG_ERR_NULL;

  if (n_us < 0)
    RAISE_ARG_ERR_NULL;

  if (n_ds < 0)
    RAISE_ARG_ERR_NULL;

  if (n_top < 0)
    RAISE_ARG_ERR_NULL;

  if (n_bot < 0)
    RAISE_ARG_ERR_NULL;

  int total_segments = n_ds + n_segments + n_us;
  int total_layers   = n_top + n_layers + n_bot;

  real **values = chl_calloc (total_segments, sizeof (real *));

  for (int i = 0; i < total_segments; i++)
    {
      *(values + i) = chl_calloc (total_layers, sizeof (real *));
    }

  ChlW2Grid g;
  NEW (g);
  g->n_segments = n_segments;
  g->n_ds       = n_ds;
  g->n_us       = n_us;
  g->n_layers   = n_layers;
  g->n_bot      = n_bot;
  g->n_top      = n_top;
  g->values     = values;

  return g;
}

void
chl_w2_grid_free (ChlW2Grid g)
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

int
chl_w2_grid_get (ChlW2Grid g, int segment, int layer, real *value)
{
  if (!g)
    RAISE_NULL_ERR_INT;

  if (segment < 1 - g->n_ds || segment > g->n_segments + g->n_us)
    RAISE_ARG_ERR_INT;

  if (layer < 1 - g->n_top || layer > g->n_layers + g->n_bot)
    RAISE_ARG_ERR_INT;

  *value = g->values[segment - 1][layer - 1];

  return 0;
}

int
chl_w2_grid_set (ChlW2Grid g, int segment, int layer, real value)
{
  if (!g)
    RAISE_NULL_ERR_INT;

  if (segment < 1 - g->n_ds || segment > g->n_segments + g->n_us)
    RAISE_ARG_ERR_INT;

  if (layer < 1 - g->n_top || layer > g->n_layers + g->n_bot)
    RAISE_ARG_ERR_INT;

  g->values[segment - 1][layer - 1] = value;

  return 0;
}
