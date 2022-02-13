/**
 * @file chlerror.h
 * @brief Error definitions
 */

#ifndef __CHL_ERR_H__
#define __CHL_ERR_H__

#if !defined(__CHL_H_INSIDE__) && !defined(CHL_COMPILATION)
#error "Only <chl.h> can be included directly."
#endif

#include <chl/chlstring.h>
#include <stdbool.h>

/**
 * Error types
 */
typedef enum
{
  /** Null argument error */
  NULL_ARGUMENT_ERROR,
  /** Invalid argument error */
  INVALID_ARGUMENT_ERROR,
  /** Memory error */
  MEMORY_ERROR
} ChlErrorType;

/**
 * chlib error object
 */
typedef struct ChlError *ChlError;

/**
 * @brief Creates a new error object
 *
 * @details The error object must be freed with chl_err_free().
 *
 * @param type error type
 * @param message error message
 */
extern ChlError chl_err_new (ChlErrorType type, const char *message);

/**
 * @brief Frees an error object.
 *
 * @param err error object
 * @returns 0 if the operation was a success, -1 otherwise.
 */
extern int chl_err_free (ChlError err);

/**
 * @brief Returns true if an error object is of a specified type.
 *
 * @param err an error object
 * @param type an error type
 * @returns true if @c err is of type @c type, false otherwise
 */
extern bool chl_err_is_type (ChlError err, ChlErrorType type);

/**
 * @brief Returns the message of an error
 *
 * @param err an error object
 * @returns the message of @c err
 */
extern ChlString chl_err_message (ChlError err);

/**
 * @brief Returns the name the type of an error
 *
 * @param err an error object
 * @returns the name of the error type of @c err
 */
extern ChlString chl_err_name (ChlError err);

/**
 * @brief Returns the string representation of an error
 *
 * @details The string representation of an error is
 *
 * <code>[error type name]: [error message]</code>
 *
 * @param err an error object
 * @returns the string representation of @c err
 */
extern ChlString chl_err_str (ChlError err);

/**
 * @brief Returns the type of an error
 *
 * @param err an error object
 * @returns the error type of @c err
 */
extern ChlErrorType chl_err_type (ChlError err);

#endif
