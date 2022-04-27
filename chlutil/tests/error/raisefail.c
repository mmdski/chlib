#include <chl/chlerror.h>

#include "test.h"

int
main (void)
{
  assert_false (chl_err_stack_is_err ());

  ChlErrorType type = INVALID_ARGUMENT_ERROR;
  assert_zero (chl_err_raise (type, "message", __FILE__, __LINE__));
  assert_true (chl_err_stack_is_err ());

  chl_err_raise (type, "message", __FILE__, __LINE__);

  return EXIT_SUCCESS;
}
