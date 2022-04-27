#ifndef __1D_SUBSECT_H__
#define __1D_SUBSECT_H__

#include <chl/chl1d.h>
#include <chl/chlmath.h>

#include "array.h"

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

/**
 * @brief Gets the roughness value of a subsection
 *
 * @param ss a subsection
 * @param roughness the roughness value
 * @return 0 if operation successful
 * @return -1 if operation fails
 */
extern int chl_xs_subsect_roughness (ChlXSSubsect ss, real *roughness);

/**
 * @brief Returns the hydraulic properties of a subsection
 *
 * @details The returned cross section properties object is newly created and
 * must be freed with chl_1d_xs_props_free().
 *
 * Area, top width, wetted perimeter, hydraulic radius, and conveyance are
 * returned.
 *
 * @param ss a subsection
 * @param h elevation
 * @return Chl1DXSProps
 */
extern Chl1DXSProps chl_xs_subsect_props (ChlXSSubsect ss, real h);

#endif
