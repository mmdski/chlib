#ifndef __XS_ARRAY_H__
#define __XS_ARRAY_H__
#include "coordinate.h"
#include <chl.h>

extern real chl_xs_array_max_y (ChlXSArray a);

extern real chl_xs_array_min_y (ChlXSArray a);

extern Coordinate chl_xs_array_get (ChlXSArray a, int i);

/**
 * chl_xs_array_subarray:
 * @a:   a #ChlXSArray
 * @zlo: low z-value of coordinate range
 * @zhi: high z-value of coordinate range
 *
 * Returns a subset of the coordinates in @a as a new coordinate array. The
 * subset is selected so that the z-values of the coordinates are between @zlo
 * and @zhi. @zlo and @zhi must be within the range of the z values of the
 * coordinates contained in @a, inclusive. The resulting coordinate array is
 * newly created and should be freed with chl_xs_array_free() when no longer
 * needed.
 *
 * Returns: a subset of @a
 */
extern ChlXSArray chl_xs_array_subarray (ChlXSArray a, real zlo, real zhi);

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
extern ChlXSArray chl_xs_array_subarray_y (ChlXSArray a, real y);

#endif
