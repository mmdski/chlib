#ifndef __CHL_REACH_H__
#define __CHL_REACH_H__
#include <stdlib.h>

#include <chl/chl_xs.h>

/**
 * @brief Reach node structure
 *
 */
struct _ChlReachNode
{
  /** Distrance downstream */
  double downstream_dist;

  /** Elevation datum */
  double elev_datum;

  /** Pointer to chlib cross section */
  void *xs;

  /** Function that computes cross section properties for @c xs */
  ChlXSPropsFunc xsp_func;
};

/**
 * @brief Reach node
 *
 */
typedef struct _ChlReachNode *ChlReachNode;

/**
 * @brief Simulation reach structure
 *
 */
struct _ChlReach
{
  /** Number of nodes in the reach */
  size_t n_nodes;

  /** Array of reach nodes */
  ChlReachNode *nodes;
};

/**
 * @brief Simulation reach
 *
 */
typedef struct _ChlReach *ChlReach;

/**
 * @brief Creates a new reach
 *
 * @details The returned reach is newly created and must be freed with
 * chl_reach_free().
 *
 * @param n_nodes number of nodes in the reach
 * @return ChlReach
 */
extern ChlReach chl_reach_new (size_t n_nodes);

/**
 * @brief Frees a reach
 *
 * @param reach simulation reach
 */
extern void chl_reach_free (ChlReach reach);

/**
 * @brief Sets the station information for a node in a reach
 *
 * @details @p chl_xs must be freed using the corresponding function to free the
 * type of the cross section. chl_reach_free() does not free @p chl_xs.
 *
 * @param reach a reach
 * @param node_idx node index
 * @param chl_xs a chlib cross section
 * @param xsp_func the function to get the cross section properties from @p
 * chl_xs
 * @param elev_datum node elevation datum
 * @param downstream_dist distance downstream
 * @return int
 */
extern int chl_reach_set_sta (ChlReach       reach,
                              size_t         node_idx,
                              void          *chl_xs,
                              ChlXSPropsFunc xsp_func,
                              double         elev_datum,
                              double         downstream_dist);

/**
 * @brief Returns the cross section from a station
 *
 * @param reach a reach
 * @param node_idx node index
 * @return void*
 */
extern void *chl_reach_get_sta (ChlReach reach, size_t node_idx);

/**
 * @brief Returns the cross section properties computed with a cross section at
 * a reach node
 *
 * @param reach a reach
 * @param node_idx node index
 * @param elev elevation for computing cross section properties
 * @param xsp_ptr pointer to cross section properties object
 * @return int
 */
extern int chl_reach_get_xsp (ChlReach    reach,
                              size_t      node_idx,
                              double      elev,
                              ChlXSProps *xsp_ptr);

extern int chl_reach_thalweg (ChlReach reach, double **thalweg);

#endif
