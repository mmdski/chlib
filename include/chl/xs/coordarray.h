#ifndef CHL_XS_COORDARRAY_H_
#define CHL_XS_COORDARRAY_H_

#include <chl/xs/coordinate.h>
#include <vector>

namespace chl {
namespace xs {

/**
 * @brief Array of cross section coordinates_
 *
 */
class CoordArray {
public:
  /**
   * @brief Construct a new Coord Array object
   *
   * @param length
   * @param station
   * @param elevation
   */
  CoordArray(size_t length, double *station, double *elevation) {

    for (size_t i = 0; i < length; ++i) {
      coordinates_.push_back(chl::xs::Coordinate(station[i], elevation[i]));
    }
  }

  CoordArray(const CoordArray &other) : coordinates_{other.coordinates_} {}

private:
  std::vector<chl::xs::Coordinate> coordinates_;
};
} // namespace xs
} // namespace chl

#endif
