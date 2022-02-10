#include "test.h"
#include <chl.h>
#include <stdlib.h>

int
main ()
{

  assert_negative (chl_xs_rect_free (NULL));

  return EXIT_SUCCESS;
}
