#include <stdlib.h>

#include <chl/chlerror.h>
#include <chl/chlw2.h>

#include "test.h"

int
main (void)
{
  chl_w2_grid_free (NULL);

  chl_err_stack_check (__FILE__, __LINE__);
  EXIT_SUCCESS;
}
