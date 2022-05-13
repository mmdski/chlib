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
