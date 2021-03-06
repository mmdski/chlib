#include <chl/chl_error.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "errorstack/file1.c"

#define FILENAME "errorstack.c"

void
check_is_err (void)
{
  bool     is_error = chl_err_stack_is_err ();
  ChlError err;
  if (is_error)
    {
      err = chl_err_stack_get_err ();
      printf ("There is an error\n");
      ChlString err_string = chl_err_str (err);
      char     *string;
      chl_string_get (err_string, &string);
      printf ("The error string: [%s]\n", string);
      chl_string_free (err_string);
    }
  else
    {
      printf ("There is no error\n");
    }
}

int
main (void)
{

  if (raise_error () < 0)
    chl_err_stack_push (FILENAME, __LINE__);

  chl_err_stack_print (FILENAME, __LINE__);

  chl_err_stack_clear ();

  chl_err_stack_print (FILENAME, __LINE__);

  return EXIT_SUCCESS;
}
