#include <string.h>

#include <chl/chl_string.h>

#include "chltest.h"

void
test_new (void)
{
  ChlString s = chl_string_new ("Hello, world!");
  chl_string_free (s);

  assert_null (chl_string_new (NULL));
}

void
test_free (void)
{
  ChlString s = chl_string_new ("Hello, world!");
  chl_string_free (s);

  chl_string_free (NULL);
}

void
test_copy (void)
{
  ChlString s      = chl_string_new ("Hello, world!");
  ChlString s_copy = chl_string_copy (s);

  char *a;
  assert_zero (chl_string_get (s, &a));

  char *b;
  assert_zero (chl_string_get (s_copy, &b));

  assert_zero (strcmp (a, b));

  chl_string_free (s);
  chl_string_free (s_copy);
}

void
test_get (void)
{
  char     *string = "Hello, world!";
  ChlString s      = chl_string_new (string);

  char *get_string;
  assert_zero (chl_string_get (s, &get_string));
  assert_zero (strcmp (get_string, string));

  chl_string_free (s);
}

void
test_eq (void)
{
  ChlString a      = chl_string_new ("abcd");
  ChlString b      = chl_string_new ("efgh");
  ChlString c      = NULL;
  ChlString a_copy = chl_string_copy (a);

  assert_true (chl_string_eq (a, a));
  assert_false (chl_string_eq (a, c));
  assert_false (chl_string_eq (a, b));
  assert_false ((a == a_copy));
  assert_true (chl_string_eq (a, a_copy));
  assert_false (chl_string_eq (NULL, NULL));

  chl_string_free (a);
  chl_string_free (b);
  chl_string_free (a_copy);
}

int
main (void)
{
  RUN_TEST_FUNC (test_new)
  RUN_TEST_FUNC (test_free)
  RUN_TEST_FUNC (test_eq)
  RUN_TEST_FUNC (test_copy)
  RUN_TEST_FUNC (test_get)

  EXIT_TEST
}
