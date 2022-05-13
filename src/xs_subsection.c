#include <assert.h>
#include <math.h>
#include <stddef.h>

#include <chl/chl_constants.h>
#include <chl/chl_error.h>

#include "error.h"
#include "list.h"
#include "memory.h"
#include "xs_array.h"
#include "xs_coordinate.h"

/* subsection interface */
struct _ChlXSSubsect
{
  ChlXSArray array; /* coordinate array */
  double     n;     /* Manning's n */
  double     min_y; /* activation depth */
};

/* Allocates memory and creates a new Subsection */
ChlXSSubsect
chl_xs_subsect_new (ChlXSArray a, double roughness)
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

int
chl_xs_subsect_roughness (ChlXSSubsect ss, double *roughness)
{
  if (ss == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "subsection is NULL", __FILE__, __LINE__);
      return -1;
    };
  *roughness = ss->n;
  return 0;
}

/* Calculates hydraulic properties for the subsection.
 * Returns a new ChlXSProps.
 */
int
chl_xs_subsect_props (ChlXSSubsect ss, double y, ChlXSProps *xsp_ptr)
{
  if (!ss)
    RAISE_NULL_ERR_INT;

  ChlXSArray sa;

  double area      = 0;
  double perimeter = 0;
  double top_width = 0;
  double hydraulic_radius;
  double conveyance;

  if (*xsp_ptr == NULL)
    *xsp_ptr = chl_xs_props_new ();

  ChlXSProps xsp = *xsp_ptr;

  int n;

  /* return 0 subsection values if this subsection isn't activated */
  if (y <= chl_xs_array_min_y (ss->array) || y <= ss->min_y)
    {
      sa = NULL;
      n  = 0;
    }
  /* otherwise calculate the values */
  else
    {
      sa = chl_xs_array_subarray_y (ss->array, y);
      n  = chl_xs_array_length (sa);
    }

  int i;

  /* depth for c1 and c2 */
  double d1;
  double d2;

  /* distances for perimeter */
  double dy;
  double dz;

  double y1;
  double z1;

  double y2;
  double z2;

  Coordinate c1;
  Coordinate c2;

  for (i = 1; i < n; i++)
    {

      c1 = chl_xs_array_get (sa, i - 1);
      c2 = chl_xs_array_get (sa, i);

      if (c1)
        {
          y1 = c1->y;
          z1 = c1->z;
        }
      else
        {
          y1 = NAN;
          z1 = NAN;
        }

      if (c2)
        {
          y2 = c2->y;
          z2 = c2->z;
        }
      else
        {
          y2 = NAN;
          z2 = NAN;
        }

      coord_free (c1);
      coord_free (c2);

      /* if y1 or y2 is NAN, continue */
      if (isnan (y1) || isnan (y2))
        {
          continue;
        }

      /* calculate area by trapezoidal integration */
      d1 = y - y1;
      d2 = y - y2;
      area += 0.5 * (d1 + d2) * (z2 - z1);

      /* calculate perimeter */
      dy = y2 - y1;
      dz = z2 - z1;
      perimeter += sqrt (dy * dy + dz * dz);

      /* calculate top width */
      top_width += z2 - z1;
    }

  hydraulic_radius = area / perimeter;

  if (area > 0)
    conveyance =
        chl_const_manning () / ss->n * area * pow (hydraulic_radius, 2.0 / 3.0);
  else
    conveyance = 0;

  chl_xs_props_set (xsp, XS_AREA, area);
  chl_xs_props_set (xsp, XS_TOP_WIDTH, top_width);
  chl_xs_props_set (xsp, XS_WETTED_PERIMETER, perimeter);
  chl_xs_props_set (xsp, XS_HYDRAULIC_RADIUS, hydraulic_radius);
  chl_xs_props_set (xsp, XS_CONVEYANCE, conveyance);

  chl_xs_array_free (sa);

  return 0;
}
