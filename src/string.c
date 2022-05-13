#include <chl/chl_string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

struct _ChlString
{
  long  len;
  char *string;
};

static ChlString
chl_string_new_empty (long len)
{
  ChlString s;
  NEW (s);

  char *string = chl_calloc (len, sizeof (char));

  if (string == NULL)
    {
      return NULL;
    }

  s->len    = len;
  s->string = string;

  return s;
}

static int
chl_string_fill (ChlString s, const char *string)
{
  if (s == NULL || string == NULL)
    {
      return -1;
    }

  long len = s->len;

  for (long i = 0; i < len; i++)
    {
      s->string[i] = string[i];
    }

  return 0;
}

ChlString
chl_string_new (const char *string)
{
  if (string == NULL)
    {
      return NULL;
    }

  long       len     = 1;
  const long MAX_LEN = 500;

  while (true)
    {
      if (string[len - 1] == '\0')
        {
          break;
        }
      else if (len >= MAX_LEN)
        {
          break;
        }
      else
        len++;
    }

  ChlString s = chl_string_new_empty (len);
  if (s == NULL)
    {
      return NULL;
    }

  if (chl_string_fill (s, string) < 0)
    {
      chl_string_free (s);
      return NULL;
    }

  return s;
}

void
chl_string_free (ChlString s)
{
  if (s == NULL)
    {
      return;
    }
  chl_free (s->string);
  FREE (s);
  return;
}

ChlString
chl_string_copy (ChlString s)
{
  if (s == NULL)
    return NULL;

  ChlString s_copy = chl_string_new (s->string);

  return s_copy;
}

bool
chl_string_eq (ChlString a, ChlString b)
{
  if (a == NULL || b == NULL)
    return false;

  if (a == b)
    return true;

  return strcmp (a->string, b->string) == 0;
}

int
chl_string_get (ChlString s, char **string)
{
  if (s == NULL || string == NULL)
    {
      return -1;
    }
  *string = s->string;
  return 0;
}

int
chl_string_len (ChlString s, long *len)
{
  if (s == NULL || len == NULL)
    {
      return -1;
    }

  *len = s->len;

  return 0;
}
