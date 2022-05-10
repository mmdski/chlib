#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "chlassert.h"

int
main (void)
{

#ifdef CHECK_ARGS
  assert_negative (chl_xs_rect_free (NULL));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();
#endif

  return EXIT_SUCCESS;
}
