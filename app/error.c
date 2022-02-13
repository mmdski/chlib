#include <chl.h>
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
  ChlError err = chl_err_new (INVALID_ARGUMENT_ERROR, NULL);

  ChlString err_string = chl_err_str (err);
  char     *string;
  chl_string_get (err_string, &string);
  printf ("%s\n", string);
  chl_string_free (err_string);

  ChlString name = chl_err_name (err);
  chl_string_get (name, &string);
  printf ("Name: %s\n", string);
  chl_string_free (name);

  ChlString message = chl_err_message (err);
  chl_string_get (message, &string);
  printf ("Message: %s\n", string);
  chl_string_free (message);

  ChlErrorType type = chl_err_type (err);
  printf ("INVALID_ARGUMENT_ERROR = %i\n", INVALID_ARGUMENT_ERROR);
  printf ("Error type: %i\n", type);

  chl_err_free (err);

  return EXIT_SUCCESS;
}
