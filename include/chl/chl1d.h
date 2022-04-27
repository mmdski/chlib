/**
 * @file chl1d.h
 * @brief 1D interface
 */

#ifndef __CHL_1D_H__
#define __CHL_1D_H__

#include <chl/chlmath.h>

/**
 * Rectangular cross section.
 */
typedef struct Chl1DRectXS *Chl1DRectXS;

/**
 * @brief Creates a new rectangular cross section
 *
 * @details Creates a new rectangular cross section. This function
 * returns @c NULL if creation fails. The returned cross section must be freed
 * with chl_1d_rectxs_free() when no longer in use.
 *
 * @param width width of cross section
 * @return new rectangular cross section
 * @return @c NULL if creation fails
 */
extern Chl1DRectXS chl_1d_rectxs_new (real width);

/**
 * @brief Frees a rectangular cross section
 *
 * @param xs cross section to free
 * @return 0 if operation was a success
 * @return -1 if operation fails
 */
extern int chl_1d_rectxs_free (Chl1DRectXS xs);

#endif
