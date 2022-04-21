#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main (void)
{

  assert_negative (chl_xs_rect_free (NULL));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));

  return EXIT_SUCCESS;
}
