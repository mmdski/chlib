#ifndef __CHL_REACH_H__
#define __CHL_REACH_H__

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

  /** Cross section properties object */
  ChlXSProps xsp;
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
 * @return ChlReach new simulation reach
 */
extern ChlReach chl_reach_new (size_t n_nodes);

/**
 * @brief Frees a reach
 *
 * @param reach simulation reach
 */
extern void chl_reach_free (ChlReach reach);

#endif
