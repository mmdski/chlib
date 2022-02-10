/**
 * @file chlxs.h
 * @brief Cross section intervation
 */

#ifndef __CHL_XS_H__
#define __CHL_XS_H__

#if !defined(__CHL_H_INSIDE__) && !defined(CHL_COMPILATION)
#error "Only <chl.h> can be included directly."
#endif

#include <chl/chlmath.h>

/**
 * Rectangular cross section object
 */
typedef struct ChlXSRect *ChlXSRect;

/**
 * @brief Creates a new rectangular cross section
 *
 * @details Creates a new rectangular cross section. This function
 * returns @c NULL if creation fails. The returned cross section must be freed
 * with chl_xs_rect_free() when no longer in use.
 *
 * @param width width of cross section
 * @return new rectangular cross section
 */
extern ChlXSRect chl_xs_rect_new (real width);

/**
 * @brief Frees a rectangular cross section
 *
 * @param x cross section to free
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int chl_xs_rect_free (ChlXSRect xs);

#endif
