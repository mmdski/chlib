#ifndef __XS_ARRAY_H__
#define __XS_ARRAY_H__

#include <stdbool.h>

#include "coordinate.h"

/**
 * @brief Cross section coordinate array
 *
 */
typedef struct ChlXSArray *ChlXSArray;

/**
 * @brief Creates a new array
 *
 * @details Creates a new coordinate array with length @p n and station and
 * elevation values of @p station and @p elevation. The resulting coordinate
 * array is newly allocated and must be freed with chl_xs_array_free().
 *
 * @param n the length of @p h and @p z
 * @param elevation pointer to an array of @p n station values
 * @param station pointer to an array of @p n elevation values
 * @return a new array
 * @return @c NULL if creation fails
 */
extern ChlXSArray chl_xs_array_new (int n, double *elevation, double *station);

/**
 * @brief Returns a new copy of an array
 *
 * @details Returns a new copy of @p a. The returned coordinate array is
 * newly allocated and should be freed using chl_xs_array_free().
 *
 * @param a an array
 * @returns a copy of @p a
 */
extern ChlXSArray chl_xs_array_copy (ChlXSArray a);

/**
 * @brief Frees a coordinate array.
 *
 */
extern void chl_xs_array_free (ChlXSArray a);

/**
 * @brief Determines if arrays are equal
 *
 * @param a1 an array
 * @param a2 another array
 * @return true if @p a1 is equal to @p a2
 * @return false if @p a1 is not equal to @p a2
 */
extern bool chl_xs_array_eq (ChlXSArray a1, ChlXSArray a2);

/**
 * @brief Gets the station and elevation values of an array
 *
 * @details @p elevation and @p station must be allocated before calling this
 * function and freed when no longer in use.
 *
 * @param a an array
 * @param elevation elevation values
 * @param station station values
 * @return int length of array
 */
extern int chl_xs_array_vals (ChlXSArray a, double *elevation, double *station);

/**
 * @brief Returns the length of an array.
 *
 * @param a an array
 * @return int the length of @p a
 */
extern int chl_xs_array_length (ChlXSArray a);

/**
 * @brief Returns a subset of the coordinate in an array
 *
 * @details The subset is selected so that the z-values of the coordinate are
 * between @p sta_lo and @p sta_hi. @p sta_lo and @p sta_hi must be within the
 * range of the station values of @p a. The resulting coordinate array is newly
 * crated and must be freed with chl_xs_array_free().
 *
 * @param a a cross section array
 * @param sta_lo low station
 * @param sta_hi hi station
 * @return ChlXSArray
 */
extern ChlXSArray
chl_xs_array_subarray (ChlXSArray a, double sta_lo, double sta_hi);

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
