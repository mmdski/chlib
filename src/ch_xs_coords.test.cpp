#include <gtest/gtest.h>

extern "C"
{
#include <chl/xs.h>
}

namespace
{

TEST (ch_xs_coords, ch_xs_coords_new)
{
  ChXSCoords *coords = ch_xs_coords_new (10);
  ASSERT_TRUE (coords);
  ch_xs_coords_free (&coords);
}

} // namespace

int
main (int argc, char **argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
