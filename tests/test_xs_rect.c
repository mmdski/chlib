#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "chltest.h"

void
test_new (void)
{
  double width = 10;

  ChlXSRect xs = chl_xs_rect_new (width);
  assert_nonnull (xs);
  assert_zero (chl_xs_rect_free (xs));

#ifdef CHECK_ARGS
  xs = NULL;
  xs = chl_xs_rect_new (-10);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  xs = chl_xs_rect_new (0);
  assert_null (xs);
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();
#endif
}

void
test_free (void)
{
#ifdef CHECK_ARGS
  assert_negative (chl_xs_rect_free (NULL));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();
#endif
}

int
main (void)
{
  RUN_TEST_FUNC (test_new)
  RUN_TEST_FUNC (test_free)

  EXIT_TEST
}
