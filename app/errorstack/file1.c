#include <chl/chl_error.h>

int
raise_error (void)
{
  chl_err_raise (INVALID_ARGUMENT_ERROR,
                 "Invalid argument",
                 "errorstack/file1.c",
                 __LINE__);
  return -1;
}
