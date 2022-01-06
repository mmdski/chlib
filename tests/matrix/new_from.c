#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main ()
{
  int n_rows     = 5;
  int n_columns  = 2;
  int n_elements = n_rows * n_columns;

  real *elements = (real *) calloc (n_elements, sizeof (real));

  ChlMatrix a = chl_matrix_new_from (n_rows, n_columns, elements);
  assert_nonnull (a);

  for (int i = 0; i < n_elements; i++)
    {
      elements[i] = rand ();
    }

  real entry;
  int  k = 0;
  for (int i = 1; i <= n_rows; i++)
    {
      for (int j = 1; j <= n_columns; j++)
        {
          assert_zero (chl_matrix_get (a, i, j, &entry));
          assert_equal (elements[k++], entry);
        }
    }

  assert_zero (chl_matrix_free (a));
  free (elements);

  return EXIT_SUCCESS;
}
