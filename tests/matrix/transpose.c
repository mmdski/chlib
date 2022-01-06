#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main ()
{
  int n_rows = 3;
  int n_cols = 2;

  ChlMatrix a = chl_matrix_new (n_rows, n_cols);
  assert_nonnull (a);

  real a_value;
  real a_t_value;

  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j <= n_cols; j++)
        {
          a_value = i + j - 1;
          assert_zero (chl_matrix_set (a, i, j, a_value));
        }
    }

  ChlMatrix a_transpose = NULL;
  assert_zero (chl_matrix_transpose (a, &a_transpose));
  assert_nonnull (a_transpose);

  for (int i = 1; i <= n_cols; i++)
    {
      for (int j = 1; j <= n_rows; j++)
        {
          assert_zero (chl_matrix_get (a, j, i, &a_value));
          assert_zero (chl_matrix_get (a_transpose, i, j, &a_t_value));
          assert_equal (a_value, a_t_value);
        }
    }

  assert_zero (chl_matrix_free (a));
  assert_zero (chl_matrix_free (a_transpose));

  return EXIT_SUCCESS;
}
