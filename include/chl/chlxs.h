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
 * @brief Cross section coordinate array
 *
 */
typedef struct ChlXSArray *ChlXSArray;

/**
 * @brief Creates a new array
 *
 * @details Creates a new coordinate array with length @p n and y- and z-values
 * of @p y and @p z. The resulting coordinate array is newly allocated and must
 * be freed with chl_xs_array_free().
 *
 * @param n the length of @p y and @p z
 * @param y pointer to an array of @p n y-values
 * @param z pointer to an array of @p n z-values
 * @return a new array
 * @return @c NULL if creation fails
 */
extern ChlXSArray chl_xs_array_new (int n, real *y, real *z);

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
 * @return 0 if successful
 * @return -1 otherrwise
 */
extern int chl_xs_array_free (ChlXSArray a);

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
 * @brief Returns the length of an array.
 *
 * @param a an array
 * @return int the length of @p a
 */
extern int chl_xs_array_length (ChlXSArray a);

/**
 * Rectangular cross section.
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
 * @return @c NULL if creation fails
 */
extern ChlXSRect chl_xs_rect_new (real width);

/**
 * @brief Frees a rectangular cross section
 *
 * @param xs cross section to free
 * @return 0 if operation was a success
 * @return -1 if operation fails
 */
extern int chl_xs_rect_free (ChlXSRect xs);

/**
 * @brief Subsection of a cross section
 *
 */
typedef struct ChlXSSubsect *ChlXSSubsect;

/**
 * @brief Creates a new subsection
 *
 * @param a a cross-section array
 * @param roughness a roughness value
 * @return ChlXSSubsect
 * @return @c NULL if creation fails
 */
extern ChlXSSubsect chl_xs_subsect_new (ChlXSArray a, real roughness);

/**
 * @brief Frees a subsection
 *
 * @param ss a subsection
 * @return 0 if operation was a success
 * @return -1 if operation fails
 */
extern int chl_xs_subsect_free (ChlXSSubsect ss);

#endif
