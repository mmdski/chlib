#include <chl.h>
#include <stdlib.h>

int
main (void)
{
  chl_err_raise (INVALID_ARGUMENT_ERROR, "", __FILE__, __LINE__);
  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
