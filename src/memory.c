#include <stdlib.h>

void *
chl_alloc (size_t nbytes)
{
  return malloc (nbytes);
}

void *
chl_calloc (size_t count, size_t nbytes)
{
  return calloc (count, nbytes);
}

void
chl_free (void *ptr)
{
  free (ptr);
}
