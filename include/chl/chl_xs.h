/**
 * @file chl_xs.h
 * @brief cross section interface
 */

#ifndef __CHL_XS_H__
#define __CHL_XS_H__

#include <stdbool.h>

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
} ChlXSPropNum;

/**
 * @brief Data type for hydraulic properties of a cross section
 *
 */
typedef struct ChlXSProps *ChlXSProps;

/**
 * @brief Initializes an empty cross section properties object
 *
 * @return ChlXSProps
 */
extern ChlXSProps chl_xs_props_new (void);

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
extern int chl_xs_props_get (ChlXSProps xsp, ChlXSPropNum prop, double *value);

/**
 * @brief Rectangular cross section structure
 *
 */
struct ChlXSRect_s
{
  /** Cross section width */
  double width;

  /** Cross section roughness */
  double roughness;
};

/**
 * Rectangular cross section.
 */
typedef struct ChlXSRect_s *ChlXSRect;

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
extern ChlXSRect chl_xs_rect_new (double width);

/**
 * @brief Frees a rectangular cross section
 *
 * @param xs cross section to free
 * @return 0 if operation was a success
 * @return -1 if operation fails
 */
extern int chl_xs_rect_free (ChlXSRect xs);

/**
 * @brief Returns the cross secton properties of a rectangular cross section
 *
 * @param xs a rectangular cross section
 * @param y depth
 * @param xsp_ptr pointer to a cross section properties object (or @c NULL)
 * @return int
 */
extern int chl_xs_rect_props (ChlXSRect xs, double y, ChlXSProps *xsp_ptr);

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
extern ChlXSSubsect chl_xs_subsect_new (ChlXSArray a, double roughness);

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
extern int chl_xs_subsect_roughness (ChlXSSubsect ss, double *roughness);

/**
 * @brief Returns the hydraulic properties of a subsection
 *
 * @details The returned cross section properties object is newly created and
 * must be freed with chl_xs_props_free().
 *
 * Area, top width, wetted perimeter, hydraulic radius, and conveyance are
 * returned.
 *
 * @param ss a subsection
 * @param h elevation
 * @param xsp_ptr pointer to a cross section properties object
 * @return int
 */
extern int
chl_xs_subsect_props (ChlXSSubsect ss, double h, ChlXSProps *xsp_ptr);

/**
 * @brief Compound cross section
 *
 */
typedef struct ChlXSComp *ChlXSComp;

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
 * @return ChlXSComp
 */
extern ChlXSComp chl_xs_comp_new (int     n_coords,
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
extern void chl_xs_comp_free (ChlXSComp xs);

/**
 * @brief Returns the hydraulic properies of a compound cross section
 *
 * @details If @p *xsp is @c NULL, a new cross section properties object will be
 * created. Otherwise, the function fills @p xsp with computed cross section
 * properties. @p xsp must be freed with chl_xs_prop_free() when no longer
 * needed.
 *
 * @param xs a compound cross section
 * @param h elevation
 * @param xsp_ptr a pointer to a cross section properties object
 * @return ChlXSProps
 */
extern int chl_xs_comp_props (ChlXSComp xs, double h, ChlXSProps *xsp_ptr);

#endif
