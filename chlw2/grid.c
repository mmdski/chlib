#include <stdio.h>
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

  real **values = chl_calloc (total_segments, sizeof (real **));

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

  int n_ds       = g->n_ds;
  int n_us       = g->n_us;
  int n_segments = g->n_segments;

  int n_top    = g->n_top;
  int n_bot    = g->n_bot;
  int n_layers = g->n_layers;

  if (segment < 1 - n_ds || segment > n_segments + n_us)
    {
      char *err_msg_buff = chl_calloc (80, sizeof (char));
      sprintf (err_msg_buff,
               "Segment numer %i is invalid for grid with %i segments\n",
               segment,
               n_segments);
      chl_err_raise (INVALID_ARGUMENT_ERROR, err_msg_buff, __FILE__, __LINE__);
      chl_free (err_msg_buff);
      return -1;
    }

  if (layer < 1 - n_top || layer > n_layers + n_bot)
    {
      char *err_msg_buff = chl_calloc (80, sizeof (char));
      sprintf (err_msg_buff,
               "Layer numer %i is invalid for grid with %i layers\n",
               layer,
               n_layers);
      chl_err_raise (INVALID_ARGUMENT_ERROR, err_msg_buff, __FILE__, __LINE__);
      chl_free (err_msg_buff);
      return -1;
    }

  *value = *(*(g->values + segment - 1) + layer - 1);

  return 0;
}

int
chl_w2_grid_set (ChlW2Grid g, int segment, int layer, real value)
{
  if (!g)
    RAISE_NULL_ERR_INT;

  int n_ds       = g->n_ds;
  int n_us       = g->n_us;
  int n_segments = g->n_segments;

  int n_top    = g->n_top;
  int n_bot    = g->n_bot;
  int n_layers = g->n_layers;

  if (segment < 1 - n_ds || segment > n_segments + n_us)
    {
      char *err_msg_buff = chl_calloc (80, sizeof (char));
      sprintf (err_msg_buff,
               "Segment numer %i is invalid for grid with %i segments\n",
               segment,
               n_segments);
      chl_err_raise (INVALID_ARGUMENT_ERROR, err_msg_buff, __FILE__, __LINE__);
      chl_free (err_msg_buff);
      return -1;
    }

  if (layer < 1 - n_top || layer > n_layers + n_bot)
    {
      char *err_msg_buff = chl_calloc (80, sizeof (char));
      sprintf (err_msg_buff,
               "Layer numer %i is invalid for grid with %i layers\n",
               layer,
               n_layers);
      chl_err_raise (INVALID_ARGUMENT_ERROR, err_msg_buff, __FILE__, __LINE__);
      chl_free (err_msg_buff);
      return -1;
    }

  *(*(g->values + segment - 1) + layer - 1) = value;

  return 0;
}
