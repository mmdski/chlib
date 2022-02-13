#include "test.h"
#include <chl.h>

int
main ()
{
  ChlError err;

  for (int i = NULL_ARGUMENT_ERROR; i < NUM_ERROR_TYPES; i++)
    {
      err = chl_err_new (i, "message");
      assert_nonnull (err);
      assert_true (chl_err_is_type (err, i));
      assert_zero (chl_err_free (err));
      err = NULL;
    }

  return EXIT_SUCCESS;
}
