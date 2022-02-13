#include "chlmem.h"
#include <chl/chlerror.h>
#include <chl/chlstring.h>
#include <stdio.h>

struct ChlError
{
  ChlErrorType type;
  ChlString    error_name;
  ChlString    message;
};

ChlString
chl_err_type_name (ChlErrorType type)
{
  char *error_name;
  switch (type)
    {
    case NULL_ARGUMENT_ERROR:
      error_name = "NullArgumentError";
      break;
    case INVALID_ARGUMENT_ERROR:
      error_name = "InvalidArgumentError";
      break;
    case MEMORY_ERROR:
      error_name = "MemoryError";
      break;
    default:
      error_name = "UnnamedError";
    }

  return chl_string_new (error_name);
}

ChlError
chl_err_new (ChlErrorType type, const char *message)
{
  ChlError err;
  NEW (err);
  err->error_name = chl_err_type_name (type);

  if (message == NULL)
    err->message = chl_string_new ("");
  else
    err->message = chl_string_new (message);

  return err;
}

int
chl_err_free (ChlError err)
{
  if (err == NULL)
    return -1;

  chl_string_free (err->error_name);
  chl_string_free (err->message);

  FREE (err);

  return 0;
}

bool
chl_err_is_type (ChlError err, ChlErrorType type)
{
  if (err == NULL)
    return false;
  return (err->type == type);
}

ChlErrorType
chl_err_type (ChlError err)
{
  if (err == NULL)
    return -1;
  return err->type;
}

ChlString
chl_err_message (ChlError err)
{
  if (err == NULL)
    {
      return NULL;
    }
  if (err->message == NULL)
    return NULL;

  return chl_string_copy (err->message);
}

ChlString
chl_err_name (ChlError err)
{
  if (err == NULL)
    {
      return NULL;
    }

  return chl_string_copy (err->error_name);
}

ChlString
chl_err_str (ChlError err)
{
  if (err == NULL)
    return NULL;

  char *err_name;
  if (chl_string_get (err->error_name, &err_name) < 0)
    return NULL;

  ChlString err_str;
  char     *err_str_buffer = NULL;

  // no message, return only the error name
  if (err->message == NULL)
    {
      err_str = chl_string_new (err_name);
      if (err_str == NULL)
        goto fail;
    }
  // otherwise, return the full string
  else
    {
      long name_len;
      if (chl_string_len (err->error_name, &name_len) < 0)
        goto fail;

      long message_len;
      if (chl_string_len (err->message, &message_len) < 0)
        goto fail;

      char *message;
      if (chl_string_get (err->message, &message) < 0)
        goto fail;

      // total length: sum minus one for a null character
      long len       = name_len + message_len + 1;
      err_str_buffer = chl_calloc (len, sizeof (char));
      if (sprintf (err_str_buffer, "%s: %s", err_name, message) < 0)
        goto fail;

      err_str = chl_string_new (err_str_buffer);
      if (err_str == NULL)
        goto fail;

      chl_free (err_str_buffer);
    }

  return err_str;

fail:
  if (err_str_buffer != NULL)
    chl_free (err_str_buffer);
  return NULL;
}
