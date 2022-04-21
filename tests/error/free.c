#include "test.h"
#include <chl.h>

int
main (void)
{
  ChlError err = chl_err_new (INVALID_ARGUMENT_ERROR, "Argument is invalid");
  assert_nonnull (err);
  assert_zero (chl_err_free (err));
  assert_negative (chl_err_free (NULL));

  return EXIT_SUCCESS;
}
