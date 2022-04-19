#include "list.h"
#include "memory.h"
#include <assert.h>
#include <chl.h>
#include <math.h>
#include <stddef.h>

/* subsection interface */
struct ChlXSSubsect
{
  ChlXSArray array; /* coordinate array */
  real       n;     /* Manning's n */
  real       min_y; /* activation depth */
};

/* Allocates memory and creates a new Subsection */
ChlXSSubsect
chl_xs_subsect_new (ChlXSArray a, real roughness)
{
  if (a == NULL)
    {
      chl_err_raise (NULL_ARGUMENT_ERROR, "array is NULL", __FILE__, __LINE__);
      return NULL;
    }

  if (roughness <= 0)
    {
      chl_err_raise (VALUE_ERROR,
                     "roughness less than or equal to zero",
                     __FILE__,
                     __LINE__);
      return NULL;
    }

  ChlXSSubsect ss;
  NEW (ss);

  ss->array = chl_xs_array_copy (a);
  if (ss->array == NULL)
    {
      chl_err_stack_push (__FILE__, __LINE__);
      return NULL;
    }
  ss->n = roughness;

  return ss;
}

/* Frees memory from a previously allocated Subsection */
int
chl_xs_subsect_free (ChlXSSubsect ss)
{
  if (ss == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "subsection is NULL", __FILE__, __LINE__);
      return -1;
    }
  chl_xs_array_free (ss->array);
  FREE (ss);

  return 0;
}
