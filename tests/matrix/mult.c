#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main ()
{
  // square identity matrices
  ChlMatrix a = chl_matrix_eye (3);
  assert_nonnull (a);

  ChlMatrix b = chl_matrix_eye (3);
  assert_nonnull (b);

  ChlMatrix c = NULL;
  assert_zero (chl_matrix_mult (a, b, &c));
  assert_nonnull (c);

  assert_true (chl_matrix_eq (a, c));

  assert_zero (chl_matrix_mult (a, b, &c));
  assert_nonnull (c);

  assert_true (chl_matrix_eq (a, c));

  assert_zero (chl_matrix_free (a));
  assert_zero (chl_matrix_free (b));
  assert_zero (chl_matrix_free (c));

  return EXIT_SUCCESS;
}
