#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main ()
{
  int n_rows    = 3;
  int n_columns = 3;

  ChlMatrix m = chl_matrix_zeros (n_rows, n_columns);
  assert_nonnull (m);

  real value;

  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j <= n_columns; j++)
        {
          assert_zero (chl_matrix_get (m, i, j, &value));
          assert_zero (value);
        }
    }

  assert_zero (chl_matrix_free (m));

  return EXIT_SUCCESS;
}
