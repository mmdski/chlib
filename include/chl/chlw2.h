/**
 * @file chlw2.h
 * @author Marian Domanski (mmdski@gmail.com)
 * @brief 2D water quality interface
 * @version 0.1
 * @date 2022-04-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __CHL_W2_H__
#define __CHL_W2_H__

#include <chl/chlmath.h>

/**
 * @brief Scalar W2 grid
 *
 */
typedef struct ChlW2SGrid *ChlW2SGrid;

extern ChlW2SGrid chl_w2_sgrid_new (int n_segments, int n_layers);

extern void chl_w2_sgrid_free (ChlW2SGrid g);

extern int chl_w2_sgrid_get (ChlW2SGrid g, int segment, int layer, real *value);

extern int chl_w2_sgrid_set (ChlW2SGrid g, int segment, int layer, real value);

#endif
