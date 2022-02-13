#include "test.h"
#include <chl.h>

int
main ()
{
  ChlError err = chl_err_new (INVALID_ARGUMENT_ERROR, "Argument is invalid");
  assert_nonnull (err);
  assert_zero (chl_err_free (err));
  return EXIT_SUCCESS;
}
