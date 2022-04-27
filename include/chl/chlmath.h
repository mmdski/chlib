/**
 * @file chlmath.h
 * @brief Math definitions
 */

#ifndef __CHL_MATH_H__
#define __CHL_MATH_H__

#if defined(REAL_IS_FLOAT)
typedef float real;

#define chl_pow(a, b) powf (a, b)

#define chl_abs(a) fabsf (a)
#else
/**
 * @brief Real number type used throughout chlib
 *
 */
typedef double real;

/**
 * @brief Package power macro
 *
 */
#define chl_pow(a, b) pow (a, b)

/**
 * @brief Package absolute value macro
 *
 */
#define chl_abs(a) fabs (a)
#endif

#endif
