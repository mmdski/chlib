#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main ()
{
  int n_rows    = 3;
  int n_columns = 3;

  ChlMatrix m = chl_matrix_new (n_rows, n_columns);
  assert_nonnull (m);
  assert_zero (chl_matrix_free (m));

  // test failures
  m = NULL;
  m = chl_matrix_new (-1, -1);
  assert_null (m);

  m = NULL;
  m = chl_matrix_new (n_rows, -1);
  assert_null (m);

  m = NULL;
  m = chl_matrix_new (-1, n_columns);
  assert_null (m);

  return EXIT_SUCCESS;
}
