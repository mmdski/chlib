#include <stdlib.h>

#include <chl/chlerror.h>

#include "test.h"

void test_rect (void);
void test_comprect (void);

int
main (void)
{
  test_rect ();
  test_comprect ();

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
