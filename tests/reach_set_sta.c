#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_reach.h>

#include <chlassert.h>

int
main (void)
{
  size_t n_nodes = 1;

  ChlReach reach = chl_reach_new (n_nodes);
  assert_nonnull (reach);

  if (chl_reach_set_sta (reach, 0, NULL, NULL, 0, 0) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      return EXIT_FAILURE;
    }

#ifdef CHECK_ARGS
  assert_negative (chl_reach_set_sta (NULL, 0, NULL, NULL, 0, 0));
  assert_true (chl_err_stack_is_type (NULL_ARGUMENT_ERROR));
  chl_err_stack_clear ();

  assert_negative (chl_reach_set_sta (reach, 1, NULL, NULL, 0, 0));
  assert_true (chl_err_stack_is_type (INVALID_ARGUMENT_ERROR));
  chl_err_stack_clear ();
#endif

  chl_reach_free (reach);

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
