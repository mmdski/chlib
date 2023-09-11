#include <gtest/gtest.h>

extern "C"
{
#include <chl/xs.h>
#include <stdlib.h>
}

namespace
{

TEST (ch_xs_coords, new)
{
  ChXSCoords *coords = NULL;
  coords             = ch_xs_coords_new ();

  // non-NULL
  ASSERT_TRUE (coords);

  // zero length
  ASSERT_TRUE (ch_xs_coords_length (coords) == 0);

  ch_xs_coords_free (&coords);

  // set to NULL
  ASSERT_TRUE (coords == NULL);
}

} // namespace

int
main (int argc, char **argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
