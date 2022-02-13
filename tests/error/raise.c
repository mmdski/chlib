#include "test.h"
#include <chl.h>

int
main ()
{
  assert_false (chl_err_stack_is_err ());

  ChlErrorType type = INVALID_ARGUMENT_ERROR;
  assert_zero (chl_err_raise (type, "message", __FILE__, __LINE__));
  assert_true (chl_err_stack_is_err ());

  ChlError err = chl_err_stack_get_err ();
  assert_nonnull (err);
  assert_true (chl_err_is_type (err, type));

  chl_err_stack_clear ();
  assert_false (chl_err_stack_is_err ());

  // the error should be null after the stack is cleared
  assert_null (chl_err_stack_get_err ());
  assert_negative (chl_err_stack_push (__FILE__, __LINE__));

  return EXIT_SUCCESS;
}
