#include <assert.h>
#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_reach.h>

#include "error.h"
#include "memory.h"

ChlReach
chl_reach_new (size_t n_nodes)
{
  ChlReach reach;
  NEW (reach);

  reach->n_nodes      = n_nodes;
  ChlReachNode *nodes = chl_alloc (sizeof (ChlReachNode) * n_nodes);
  ChlReachNode  n;

  for (size_t i = 0; i < n_nodes; i++)
    {
      NEW (n);
      n->xs       = NULL;
      n->xsp_func = NULL;
      n->xsp      = NULL;
      nodes[i]    = n;
      n           = NULL;
    }

  reach->nodes = nodes;

  return reach;
}

void
chl_reach_free (ChlReach reach)
{
  if (!reach)
    return;

  size_t       n_nodes = reach->n_nodes;
  ChlReachNode n;

  for (size_t i = 0; i < n_nodes; i++)
    {
      n = reach->nodes[i];
      FREE (n);
    }

  FREE (reach->nodes);
  FREE (reach);

  return;
}

int
chl_reach_set_sta (ChlReach       reach,
                   size_t         node_idx,
                   void          *chl_xs,
                   ChlXSPropsFunc xsp_func,
                   double         elev_datum,
                   double         downstream_dist)
{
#ifdef CHECK_ARGS
  if (!reach)
    RAISE_NULL_ERR_INT;
  if (node_idx >= reach->n_nodes)
    RAISE_ARG_ERR_INT;
#else
  assert (reach);
  assert (node_idx < reach->n_nodes);
#endif

  ChlReachNode n     = reach->nodes[node_idx];
  n->downstream_dist = downstream_dist;
  n->elev_datum      = elev_datum;
  n->xs              = chl_xs;
  n->xsp_func        = xsp_func;

  return 0;
}

void *
chl_reach_get_sta (ChlReach reach, size_t node_idx)
{
#ifdef CHECK_ARGS
  if (!reach)
    RAISE_NULL_ERR_NULL;
  if (node_idx >= reach->n_nodes)
    RAISE_ARG_ERR_NULL;
#else
  assert (reach);
  assert (node_idx < reach->n_nodes);
#endif

  return reach->nodes[node_idx]->xs;
}
