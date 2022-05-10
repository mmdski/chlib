#include <chl/chl_error.h>

#include "chlassert.h"

int
main (void)
{
  ChlError err = chl_err_new (INVALID_ARGUMENT_ERROR, "Argument is invalid");
  assert_nonnull (err);
  chl_err_free (err);
  chl_err_free (NULL);

  return EXIT_SUCCESS;
}
