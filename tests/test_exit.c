#include <stdlib.h>

#include <chl/chl_exit.h>

#include "chlassert.h"

int
main (void)
{

  chl_exit_expected_set ();
  chl_exit (EXIT_FAILURE);
  assert_true (chl_exit_called ());
  assert_equal (chl_exit_status (), EXIT_FAILURE);

  return EXIT_SUCCESS;
}
