#ifndef CHL_XS_COORD_H_
#define CHL_XS_COORD_H_

namespace chl {
namespace xs {

/**
 * @brief Cross section coordinate containing station and elevation
 *
 */
class Coordinate {
public:
  Coordinate() : station_{0}, elevation_{0} {}

  Coordinate(double station, double elevation)
      : station_{station}, elevation_{elevation} {}

  // copy constructor
  Coordinate(const Coordinate &other) noexcept
      : station_{other.station_}, elevation_{other.elevation_} {}

  // copy assignment operator
  Coordinate &operator=(const Coordinate &other) {
    station_ = other.station_;
    elevation_ = other.elevation_;
    return *this;
  }

  /**
   * @brief Returns the station of this coordinate
   *
   * @return double
   */
  double station() const { return station_; }

  /**
   * @brief Returns the elevation of this coordinate
   *
   * @return double
   */
  double elevation() const { return elevation_; }

private:
  double station_;
  double elevation_;
};

// equality operator
bool operator==(const Coordinate &a, const Coordinate &b) {

  if (&a == &b)
    return true;

  return (a.station() == b.station()) && (a.elevation() == b.elevation());
}

// inequality operator
bool operator!=(const Coordinate &a, const Coordinate &b) { return !(a == b); }
} // namespace xs
} // namespace chl

#endif
