#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main ()
{
  real width = 10;

  ChlXSRect xs = chl_xs_rect_new (width);
  assert_nonnull (xs);
  assert_zero (chl_xs_rect_free (xs));

  xs = NULL;
  xs = chl_xs_rect_new (-10);
  assert_null (xs);

  xs = chl_xs_rect_new (0);
  assert_null (xs);

  return EXIT_SUCCESS;
}
