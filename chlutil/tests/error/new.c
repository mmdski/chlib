#include <chl/chlerror.h>

#include "test.h"

int
main (void)
{
  ChlError err = chl_err_new (INVALID_ARGUMENT_ERROR, "Argument is invalid");
  assert_nonnull (err);
  chl_err_free (err);
  return EXIT_SUCCESS;
}
