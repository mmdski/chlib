#include <chl/chlerror.h>

int
raise_error (void)
{
  chl_err_raise (
      INVALID_ARGUMENT_ERROR, "Invalid argument", __FILE__, __LINE__);
  return -1;
}
