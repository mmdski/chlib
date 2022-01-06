#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main ()
{
  int n_rows    = 3;
  int n_columns = 2;

  ChlMatrix m = chl_matrix_zeros (n_rows, n_columns);
  assert_nonnull (m);
  assert_equal (chl_matrix_rows (m), n_rows);
  assert_equal (chl_matrix_cols (m), n_columns);
  assert_zero (chl_matrix_free (m));

  return EXIT_SUCCESS;
}
