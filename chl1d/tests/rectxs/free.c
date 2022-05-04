#include <stdlib.h>

#include <chl/chl1d.h>
#include <chl/chlerror.h>

#include "test.h"

int
main (void)
{

#ifdef CHECK_ARGS
  assert_negative (chl_1d_rectxs_free (NULL));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();
#endif

  return EXIT_SUCCESS;
}
