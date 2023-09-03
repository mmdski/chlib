#include <gtest/gtest.h>

#include <chl/xs/coordinate.h>

using namespace chl::xs;

namespace {

TEST(Coordinate, ConstructorTest) {
  Coordinate a = Coordinate();
  ASSERT_EQ(a.station(), 0);
  ASSERT_EQ(a.elevation(), 0);

  double station = 1.0;
  double elevation = 1.0;
  Coordinate b = Coordinate(station, elevation);
  ASSERT_EQ(b.station(), station);
  ASSERT_EQ(b.elevation(), elevation);
}

TEST(Coordinate, CopyTest) {
  Coordinate a = Coordinate(10, 100);
  Coordinate b = Coordinate(a);

  ASSERT_EQ(a, b);
}

} // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
