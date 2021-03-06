#include <stdio.h>
#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_exit.h>
#include <chl/chl_io.h>

#include "memory.h"

#define FILENAME "error.c"

struct _ChlError
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
    case VALUE_ERROR:
      error_name = "ValueError";
      break;
    case EXIT_CALLED:
      error_name = "ExitError";
      break;
    case GENERAL_ERROR:
      error_name = "GeneralError";
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
  err->type       = type;
  err->error_name = chl_err_type_name (type);

  if (message == NULL)
    err->message = chl_string_new ("");
  else
    err->message = chl_string_new (message);

  return err;
}

void
chl_err_free (ChlError err)
{
  if (err == NULL)
    return;

  chl_string_free (err->error_name);
  chl_string_free (err->message);

  FREE (err);
}

bool
chl_err_is_type (ChlError err, ChlErrorType type)
{
  if (err == NULL)
    return false;
  return ((err->type) == type);
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

      char err_str_buffer[500];
      if (chl_sprintf (err_str_buffer, "%s: %s", err_name, message) < 0)
        goto fail;

      err_str = chl_string_new (err_str_buffer);
      if (err_str == NULL)
        goto fail;
    }

  return err_str;

fail:
  return NULL;
}

typedef struct _ChlErrorStackNode ChlErrorStackNode;

struct _ChlErrorStackNode
{
  int                line;
  ChlString          file;
  ChlString          string;
  ChlErrorStackNode *next;
};

struct _ChlErrorStack
{
  ChlError           error;
  ChlErrorStackNode *node;
};

static struct _ChlErrorStack stack = { NULL, NULL };

static ChlErrorStackNode *
chl_err_stack_node_new (const char *file, int line)
{
  if (file == NULL)
    return NULL;

  ChlErrorStackNode *node;
  NEW (node);

  char node_string_buffer[500];

  node->line = line;
  node->file = chl_string_new (file);

  chl_sprintf (node_string_buffer, "File \"%s\", line %i", file, line);
  node->string = chl_string_new (node_string_buffer);

  node->next = NULL;

  return node;
}

static int
chl_err_stack_node_free (ChlErrorStackNode *node)
{
  if (node == NULL)
    return -1;

  chl_string_free (node->file);
  chl_string_free (node->string);
  FREE (node);
  return 0;
}

int
chl_err_raise (ChlErrorType type,
               const char  *message,
               const char  *file,
               int          line)
{
  if (stack.error != NULL)
    {
      fprintf (stderr, "Fatal error: Error raised while error in stack\n");
      chl_exit (EXIT_FAILURE);
#ifdef TESTING
      return EXIT_CALLED;
#endif
    }

  stack.error = chl_err_new (type, message);
  stack.node  = chl_err_stack_node_new (file, line);

  return 0;
}

bool
chl_err_stack_is_err (void)
{
  return stack.error != NULL;
}

void
chl_err_stack_clear (void)
{

  if (stack.error == NULL)
    return;

  chl_err_free (stack.error);
  stack.error = NULL;

  ChlErrorStackNode *node      = stack.node;
  ChlErrorStackNode *next_node = node->next;
  chl_err_stack_node_free (node);
  while (next_node != NULL)
    {
      node      = next_node;
      next_node = node->next;
      chl_err_stack_node_free (node);
    }
  stack.node = NULL;
}

ChlError
chl_err_stack_get_err (void)
{
  return stack.error;
}

int
chl_err_stack_push (const char *file, int line)
{
  if (stack.error == NULL || stack.node == NULL)
    return -1;

  ChlErrorStackNode *new_node = chl_err_stack_node_new (file, line);

  new_node->next = stack.node;
  stack.node     = new_node;

  return 0;
}

bool
chl_err_stack_is_type (ChlErrorType type)
{
  return chl_err_is_type (stack.error, type);
}

void
chl_err_stack_print (const char *file, int line)
{
  if (stack.error == NULL)
    return;

  fprintf (stderr, "Error stack print called from %s on line %i\n", file, line);
  fprintf (stderr, "Stack trace (most recent call last):\n");

  char *string;

  ChlErrorStackNode *node = stack.node;
  while (node != NULL)
    {
      chl_string_get (node->string, &string);
      fprintf (stderr, "\t%s\n", string);
      node = node->next;
    }

  ChlString err_string = chl_err_str (stack.error);
  chl_string_get (err_string, &string);
  fprintf (stderr, "%s\n", string);
  chl_string_free (err_string);
}

void
chl_err_stack_check (const char *file, int line)
{
  if (chl_err_stack_is_err ())
    {
      fprintf (stderr, "Unchecked error\n");
      fprintf (stderr, "Error stack checked on %s, line %i\n", file, line);
      chl_err_stack_print (FILENAME, __LINE__);
      chl_exit (EXIT_FAILURE);
    }
}
