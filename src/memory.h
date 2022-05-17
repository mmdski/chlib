#include <stdlib.h>

extern void *chl_alloc (size_t nbytes);

extern void *chl_calloc (size_t count, size_t nbytes);

extern void chl_free (void *ptr);

#define ALLOC(nbytes) chl_alloc ((nbytes))
#define NEW(p) ((p) = ALLOC (sizeof *(p)))
#define FREE(ptr) ((void) (chl_free ((ptr)), (ptr) = 0))
