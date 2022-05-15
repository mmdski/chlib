#ifndef __CHL_EXIT__
#define __CHL_EXIT__

#ifdef TESTING
#include <stdbool.h>

/**
 * @brief Perform normal program termination
 *
 * @details This function is defined for testing purposes when -DTESTING is set.
 * If the exit expected flag is set after using chl_exit_expected_set(), the
 * program doesn't terminate. The call status of this function can be checked
 * with chl_exit_called(), and the call flag can ge cleared with
 * chl_exit_called_clear(). The program will terminate if the expected flag is
 * not set or if the called flag has not been cleared.
 *
 * @param status exit status
 */
extern void chl_exit (int status);

/**
 * @brief Checks the chl_exit() call status flag
 *
 * @return true
 * @return false
 */
extern bool chl_exit_called (void);

/**
 * @brief Clears the chl_exit() call status flag
 *
 */
extern void chl_exit_called_clear (void);

/**
 * @brief Sets the chl_exit() call expected flag
 *
 */
extern void chl_exit_expected_set (void);

/**
 * @brief Clears the chl_exit() call expected flag
 *
 */
extern void chl_exit_expected_clear (void);

/**
 * @brief Returns the status from the chl_exit() call
 *
 * @return int the exit status
 */
extern int chl_exit_status (void);

#else

#define chl_exit(status) exit (status)

#endif
#endif
