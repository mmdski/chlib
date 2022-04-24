#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define assert_equal(a, b) assert (a == b);
#define assert_false(a) assert (a == false);
#define assert_positive(a) assert (a > 0);
#define assert_zero(a) assert (a == 0);
#define assert_negative(a) assert (a < 0);
#define assert_nonnull(a) assert (a != NULL);
#define assert_null(a) assert (a == NULL);
#define assert_true(a) assert (a == true);

// clang-format off
#ifdef REAL_IS_FLOAT
#define assert_approx_eq(a, b, eps) assert(fabsf(a - b) < eps)
#else
#define assert_approx_eq(a, b, eps) assert(fabs(a - b) < eps)
#endif
// clang-format on
