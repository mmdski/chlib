#include <chl/chl_error.h>
#include <chl/chl_exit.h>

#include "chltest.h"

void
test_new (void)
{
  ChlError err = chl_err_new (INVALID_ARGUMENT_ERROR, "Argument is invalid");
  assert_nonnull (err);
  chl_err_free (err);
}

void
test_free (void)
{
  ChlError err = chl_err_new (INVALID_ARGUMENT_ERROR, "Argument is invalid");
  assert_nonnull (err);
  chl_err_free (err);
  chl_err_free (NULL);
}

void
test_raise (void)
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
}

void
test_stack_check (void)
{
  chl_err_stack_check (__FILE__, __LINE__);
}

void
test_raise_fail (void)
{

  assert_false (chl_err_stack_is_err ());

  ChlErrorType type = INVALID_ARGUMENT_ERROR;
  assert_zero (chl_err_raise (type, "message", __FILE__, __LINE__));
  assert_true (chl_err_stack_is_err ());

  EXPECT_EXIT_CALL (chl_err_raise (type, "message", __FILE__, __LINE__))

  chl_err_stack_clear ();
}

void
test_stack_check_fail (void)
{
  chl_err_raise (INVALID_ARGUMENT_ERROR, "", __FILE__, __LINE__);
  chl_exit_expected_set ();
  chl_err_stack_check (__FILE__, __LINE__);
  assert_true (chl_exit_called ());
  chl_exit_called_clear ();
  chl_err_stack_clear ();
}

int
main (void)
{
  RUN_TEST_FUNC (test_new)
  RUN_TEST_FUNC (test_free)
  RUN_TEST_FUNC (test_raise)
  RUN_TEST_FUNC (test_raise_fail)
  RUN_TEST_FUNC (test_stack_check)
  RUN_TEST_FUNC (test_stack_check_fail)

  EXIT_TEST
}
