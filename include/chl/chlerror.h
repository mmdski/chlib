/**
 * @file chlerror.h
 * @brief Error definitions
 */

#ifndef __CHL_ERR_H__
#define __CHL_ERR_H__

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
  MEMORY_ERROR,
  /** Value error */
  VALUE_ERROR,
  /** Number of error types */
  NUM_ERROR_TYPES
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
 */
extern void chl_err_free (ChlError err);

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

/**
 * @brief Puts an error on the error stack and initializes the first line of the
 * stack
 *
 * @param type error type
 * @param message error message
 * @param file use __FILE__ macro
 * @param line use __LINE__ macro
 * @return 0 if successful, -1 otherwise
 */
extern int chl_err_raise (ChlErrorType type,
                          const char  *message,
                          const char  *file,
                          int          line);

/**
 * @brief Returns true if an error is on the error stack, false otherwise
 *
 * @return true or false
 */
extern bool chl_err_stack_is_err (void);

/**
 * @brief Clears the error stack
 */
extern void chl_err_stack_clear (void);

/**
 * @brief Pushes a new line on the error stack
 *
 * @param file use __FILE__ macro
 * @param line use __LINE__ macro
 * @return 0 if successful, -1 otherwise
 */
extern int chl_err_stack_push (const char *file, int line);

/**
 * @brief Returns the error currently on the error stack
 *
 * @details The returned error is a reference to the error on the stack. Do not
 * free outside of chl_err_stack_clear().
 *
 * @return error currently on the stack
 */
extern ChlError chl_err_stack_get_err (void);

/**
 * @brief Checks the error type on the error stack
 *
 * @param type error type
 * @return true if @p type is the type of error on the stack
 * @return false if @p type is not the type of error on the stack
 */
extern bool chl_err_stack_is_type (ChlErrorType type);

/**
 * @brief Print the error stack to @c stderr
 *
 */
extern void chl_err_stack_print (void);

/**
 * @brief Checks for an error on stack.
 *
 * @details If an error on the stack exists, prints the stack and exits the
 * program.
 *
 * @param file use __FILE__ macro
 * @param line use __LINE__ macro
 */
extern void chl_err_stack_check (const char *file, int line);

#endif
