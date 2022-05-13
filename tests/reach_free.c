#include <stdlib.h>

#include <chl/chl_reach.h>

#include "chlassert.h"

int
main (void)
{

  size_t n_nodes = 10;

  ChlReach reach = chl_reach_new (n_nodes);
  assert_nonnull (reach);

  chl_reach_free (reach);
  reach = NULL;

  chl_reach_free (reach);
  assert_null (reach);

  return EXIT_SUCCESS;
};
