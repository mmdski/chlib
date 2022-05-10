#include <stdlib.h>

#include <chl/chl_error.h>

#include "chlassert.h"

#include "xs_comp_props_comprect.c"
#include "xs_comp_props_rect.c"

int
main (void)
{
  test_rect ();
  test_comprect ();

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
