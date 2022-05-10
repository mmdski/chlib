/**
 * @file chl_constants.h
 * @author Marian Domanski (mmdski@gmail.com)
 * @brief Physical constants
 * @version 0.1
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __CHL_CONST_H__
#define __CHL_CONST_H__

/**
 * @brief Returns the acceleration due to gravity [L/T^2]
 *
 * @return acceleration due to gravity
 */
extern double chl_const_gravity (void);

/**
 * @brief Returns the conversion factor k from Manning's formula
 *
 * @return Manning formula conversion factor
 */
extern double chl_const_manning (void);

/**
 * @brief Sets the acceleration due to gravity
 *
 * @param gravity acceleration due to gravity
 */
extern void chl_const_set_gravity (double gravity);

/**
 * @brief Sets the Manning formula conversion factor
 *
 * @param k Manning formula conversion factor
 */
extern void chl_const_set_manning (double k);

#endif
