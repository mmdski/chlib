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

/**
 * @brief Generic W2 grid
 *
 */
typedef struct ChlW2Grid *ChlW2Grid;

extern ChlW2Grid chl_w2_grid_new (
    int n_segments, int n_layers, int n_us, int n_ds, int n_top, int n_bot);

extern void chl_w2_grid_free (ChlW2Grid g);

extern int chl_w2_grid_get (ChlW2Grid g, int segment, int layer, double *value);

extern int chl_w2_grid_set (ChlW2Grid g, int segment, int layer, double value);

#endif
