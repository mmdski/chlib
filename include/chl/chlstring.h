/**
 * @file chlstring.h
 * @brief String interface
 */

#ifndef __CHL_STRING_H__
#define __CHL_STRING_H__

#if !defined(__CHL_H_INSIDE__) && !defined(CHL_COMPILATION)
#error "Only <chl.h> can be included directly."
#endif

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
 * @return 0 if operation was a success, -1 otherwise
 */
extern int chl_string_free (ChlString s);

/**
 * @brief Copies a string
 *
 * @param s string to copy
 * @return a copy of s
 */
extern ChlString chl_string_copy (ChlString s);

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
 * @param len a pointer to a long that contains the length of @param s
 * @returns 0 if operation was a success, -1 otherwise
 */
extern int chl_string_len (ChlString s, long *len);

#endif
