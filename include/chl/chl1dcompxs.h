/**
 * @file chl1dcompxs.h
 * @brief 1D compound cross section interface
 */

#ifndef __CHL_1D_COMPXS_H__
#define __CHL_1D_COMPXS_H__

#include <stdbool.h>

#include <chl/chlmath.h>

/**
 * @brief Hydraulic properties of a cross section
 *
 */
typedef enum
{
  /** Depth associated with the properties */
  XS_DEPTH,
  /** Wetted area */
  XS_AREA,
  /** Top width */
  XS_TOP_WIDTH,
  /** Wetted perimeter */
  XS_WETTED_PERIMETER,
  /** Hydraulic depth */
  XS_HYDRAULIC_DEPTH,
  /** Hydraulic radius */
  XS_HYDRAULIC_RADIUS,
  /** Conveyance */
  XS_CONVEYANCE,
  /** Velocity coefficient (alpha) */
  XS_VELOCITY_COEFF,
  /** Critical flow */
  XS_CRITICAL_FLOW,
  N_XSP
} ChlXSPropType;

/**
 * @brief Data type for hydraulic properties of a cross section
 *
 */
typedef struct ChlXSProps *ChlXSProps;

/**
 * @brief Frees a cross section properties object
 *
 * @param xsp
 */
extern void chl_xs_props_free (ChlXSProps xsp);

/**
 * @brief Returns cross section property values
 *
 * @param xsp a cross section properties object
 * @param prop property to return
 * @param value pointer to cross section property value
 * @return int
 */
extern int chl_xs_props_get (ChlXSProps xsp, ChlXSPropType prop, real *value);

/**
 * @brief Compound cross section
 *
 */
typedef struct ChlXSCompound *ChlXSCompound;

/**
 * @brief Creates a new compound cross section
 *
 * @details Creates a new compound cross section from station, elevation
 * coordinates, roughness values, and subsection stations. The number of
 * subsection stations is equal to one less than the number of roughness values
 * provided.
 *
 * @param n_coords number of coordinates in @p station and @p elevation
 * @param elevation elevation values of coordinates
 * @param station station values of coordinates
 * @param n_roughness number of values in @p roughness
 * @param roughness n-values for each subsection
 * @param sub_station break points for subsections
 * @return ChlXSCompound
 */
extern ChlXSCompound chl_xs_comp_new (int   n_coords,
                                      real *elevation,
                                      real *station,
                                      int   n_roughness,
                                      real *roughness,
                                      real *sub_station);

/**
 * @brief Frees a compound cross section
 *
 * @param xs a compound cross section
 */
extern void chl_xs_comp_free (ChlXSCompound xs);

/**
 * @brief Returns the hydraulic properies of a compound cross section
 *
 * @details The returned cross section properties object is newly created and
 * must be freed with chl_xs_props_free().
 *
 * @param xs a compound cross section
 * @param h elevation
 * @return ChlXSProps
 */
extern ChlXSProps chl_xs_comp_props (ChlXSCompound xs, real h);

#endif
