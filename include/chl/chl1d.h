/**
 * @file chl1d.h
 * @brief 1D interface
 */

#ifndef __CHL_1D_H__
#define __CHL_1D_H__

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
} Chl1DXSPropNum;

/**
 * @brief Data type for hydraulic properties of a cross section
 *
 */
typedef struct Chl1DXSProps *Chl1DXSProps;

/**
 * @brief Frees a cross section properties object
 *
 * @param xsp
 */
extern void chl_1d_xs_props_free (Chl1DXSProps xsp);

/**
 * @brief Returns cross section property values
 *
 * @param xsp a cross section properties object
 * @param prop property to return
 * @param value pointer to cross section property value
 * @return int
 */
extern int
chl_1d_xs_props_get (Chl1DXSProps xsp, Chl1DXSPropNum prop, double *value);

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
extern Chl1DRectXS chl_1d_rectxs_new (double width);

/**
 * @brief Frees a rectangular cross section
 *
 * @param xs cross section to free
 * @return 0 if operation was a success
 * @return -1 if operation fails
 */
extern int chl_1d_rectxs_free (Chl1DRectXS xs);

/**
 * @brief Compound cross section
 *
 */
typedef struct Chl1DCompXS *Chl1DCompXS;

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
 * @return Chl1DCompXS
 */
extern Chl1DCompXS chl_1d_compxs_new (int     n_coords,
                                      double *elevation,
                                      double *station,
                                      int     n_roughness,
                                      double *roughness,
                                      double *sub_station);

/**
 * @brief Frees a compound cross section
 *
 * @param xs a compound cross section
 */
extern void chl_1d_compxs_free (Chl1DCompXS xs);

/**
 * @brief Returns the hydraulic properies of a compound cross section
 *
 * @details The returned cross section properties object is newly created and
 * must be freed with chl_1d_xs_props_free().
 *
 * @param xs a compound cross section
 * @param h elevation
 * @return Chl1DXSProps
 */
extern Chl1DXSProps chl_1d_compxs_props (Chl1DCompXS xs, double h);

#endif
