#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define assert_true(a) assert (a == true);
#define assert_false(a) assert (a == false);
#define assert_null(a) assert (a == NULL);
#define assert_nonnull(a) assert (a != NULL);
#define assert_equal(a, b) assert (a == b);
#define assert_zero(a) assert (a == 0);
