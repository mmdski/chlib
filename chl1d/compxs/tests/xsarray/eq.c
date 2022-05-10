#include "array.h"
#include "test.h"

int
main (void)
{
  int n1 = 4;
  int n2 = 4;
  int n3 = 5;

  double y1[] = { 1, 0, 0, 1 };
  double z1[] = { 0, 0, 1, 1 };

  double y2[] = { 1, 2, 0, 1 };
  double z2[] = { -1, 0, 1, 1 };

  double y3[] = { 1, 0, 0, 0, 1 };
  double z3[] = { 0, 0, 1, 1, 1 };

  ChlXSArray a1 = chl_xs_array_new (n1, y1, z1);
  assert_nonnull (a1);

  ChlXSArray a2 = chl_xs_array_new (n2, y2, z2);
  assert_nonnull (a2);

  ChlXSArray a3 = chl_xs_array_new (n3, y3, z3);
  assert_nonnull (a3);

  ChlXSArray a4 = chl_xs_array_new (n1, y1, z1);
  assert_nonnull (a4);

  assert_false (chl_xs_array_eq (NULL, NULL));
  assert_false (chl_xs_array_eq (NULL, a1));
  assert_false (chl_xs_array_eq (a1, NULL));

  assert_true (chl_xs_array_eq (a1, a1));
  assert_true (chl_xs_array_eq (a1, a4));
  assert_true (chl_xs_array_eq (a4, a1));

  assert_false (chl_xs_array_eq (a1, a2));
  assert_false (chl_xs_array_eq (a2, a1));

  assert_false (chl_xs_array_eq (a1, a3));
  assert_false (chl_xs_array_eq (a3, a1));

  chl_xs_array_free (a1);
  chl_xs_array_free (a2);
  chl_xs_array_free (a3);
  chl_xs_array_free (a4);

  return EXIT_SUCCESS;
}
