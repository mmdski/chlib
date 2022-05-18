#include <stdlib.h>

#include <chl/chl_exit.h>

#include "chltest.h"

#define FILENAME "tests/test_exit.c"

int
main (void)
{

  chl_exit_expected_set ();
  chl_exit (EXIT_FAILURE);
  assert_true (chl_exit_called ());
  assert_equal (chl_exit_status (), EXIT_FAILURE);
  chl_exit_expected_clear ();
  chl_exit_called_clear ();

  EXIT_TEST
}
