#include <stdio.h>
#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_exit.h>

#include "chlassert.h"

#define EXIT_TEST                                                              \
  chl_err_stack_check (__FILE__, __LINE__);                                    \
  assert_false (chl_exit_called ());                                           \
  return EXIT_SUCCESS;

#define STR(x) #x
#define RUN_TEST_FUNC(func)                                                    \
  printf ("Running test function: %s\n", STR (func));                          \
  func ();

#define EXPECT_EXIT_CALL(func_call)                                            \
  chl_exit_expected_set ();                                                    \
  func_call;                                                                   \
  assert_true (chl_exit_called ());                                            \
  chl_exit_expected_clear ();                                                  \
  chl_exit_called_clear ();
