#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_reach.h>
#include <chl/chl_xs.h>

#include "chlassert.h"

int
test_xsp_func (void *xs, double y, ChlXSProps *xsp_ptr)
{
  if (*xsp_ptr == NULL)
    {
      *xsp_ptr = chl_xs_props_new ();
    }

  ChlXSProps xsp = *xsp_ptr;
}

int
main (void)
{
  size_t   n_nodes = 10;
  ChlReach reach   = chl_reach_new (n_nodes);
}
