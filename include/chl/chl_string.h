/**
 * @file chl_string.h
 * @brief String interface
 */

#ifndef __CHL_STRING_H__
#define __CHL_STRING_H__

#include <stdbool.h>

/**
 * String object
 */
typedef struct ChlString *ChlString;

/**
 * @brief Creates a new string
 *
 * @details Creates a new string from a null-terminated array of characters.
 * This function returns @c NULL if creation fails. The returned string must be
 * freed with chl_string_free() when no longer in use.
 *
 * @param string null-terminated string
 * @return new string
 */
extern ChlString chl_string_new (const char *string);

/**
 * @brief Frees a string
 *
 * @param s a string
 */
extern void chl_string_free (ChlString s);

/**
 * @brief Copies a string
 *
 * @param s string to copy
 * @return a copy of s
 */
extern ChlString chl_string_copy (ChlString s);

/**
 * @brief Returns true if two strings are equal
 *
 * @param a a string
 * @param b another string
 * @return true if two strings are equal, false otherwise
 */
extern bool chl_string_eq (ChlString a, ChlString b);

/**
 * @brief Gets the character array contained in a string
 *
 * @param s a string
 * @param string a pointer to a character array
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int chl_string_get (ChlString s, char **string);

/**
 * @brief Gets the length of a string
 *
 * @details Gets the length of a string including the null character.
 *
 * @param s a string
 * @param len a pointer to a long that contains the length of s
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int chl_string_len (ChlString s, long *len);

#endif
