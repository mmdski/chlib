#ifndef __XS_ARRAY_H__
#define __XS_ARRAY_H__

#include <stdbool.h>

#include <chl/chl_xs.h>

#include "xs_coordinate.h"

extern double chl_xs_array_max_y (ChlXSArray a);

extern double chl_xs_array_min_y (ChlXSArray a);

extern Coordinate chl_xs_array_get (ChlXSArray a, int i);

/**
 * chl_xs_array_subarray_y:
 * @a:   a #ChlXSArray
 * @yhi: high y-value of coordinate range
 *
 * Returns a subset of the coordinates in @a as a new #ChlXSArray. The subset is
 * selected so that the y-values of the coordinates are less than @yhi.
 * Interpolated coordinates are added to the ends of the subarray if @yhi
 * doesn't exactly define the y-values of the first and last coordinates in
 * @a. The resulting #ChlXSArray is newly created and should be freed with
 * chl_xs_array_free() when no longer needed.
 *
 * Returns: a subset of @a
 */
extern ChlXSArray chl_xs_array_subarray_y (ChlXSArray a, double y);

#endif
