#include "test.h"
#include <chl.h>
#include <stdbool.h>
#include <stdlib.h>

int
main ()
{
  // basic test for identity matrices
  int       n  = 3;
  ChlMatrix a  = chl_matrix_eye (n);
  ChlMatrix b  = chl_matrix_eye (n);
  ChlMatrix c  = chl_matrix_eye (2);
  ChlMatrix z1 = chl_matrix_zeros (n, n);
  ChlMatrix z2 = chl_matrix_zeros (2, 2);

  assert_false (chl_matrix_eq (NULL, NULL));
  assert_true (chl_matrix_eq (a, a));
  assert_true (chl_matrix_eq (a, b));
  assert_true (chl_matrix_eq (b, a));
  assert_false (chl_matrix_eq (a, c));
  assert_false (chl_matrix_eq (a, z1));
  assert_false (chl_matrix_eq (a, z2));

  assert_zero (chl_matrix_free (a));
  assert_zero (chl_matrix_free (b));
  assert_zero (chl_matrix_free (c));
  assert_zero (chl_matrix_free (z1));
  assert_zero (chl_matrix_free (z2));

  return EXIT_SUCCESS;
}
