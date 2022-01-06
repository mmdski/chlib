#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main ()
{
  int n = 3;

  ChlMatrix m = chl_matrix_eye (n);
  assert (m != NULL);

  real value;
  real expected;

  for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= n; j++)
        {
          if (i == j)
            expected = 1;
          else
            expected = 0;

          assert_zero (chl_matrix_get (m, i, j, &value));
          assert_equal (value, expected);
        }
    }

  assert_zero (chl_matrix_free (m));

  return EXIT_SUCCESS;
}
