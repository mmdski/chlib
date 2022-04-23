#include <assert.h>
#include <chl.h>
#include <math.h>
#include <stddef.h>

#include "array.h"
#include "coordinate.h"
#include "list.h"
#include "memory.h"
#include "properties.h"

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

int
chl_xs_subsect_roughness (ChlXSSubsect ss, real *roughness)
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
ChlXSProps
subsection_properties (ChlXSSubsect ss, real y)
{
  assert (ss);

  ChlXSArray sa;

  real area      = 0;
  real perimeter = 0;
  real top_width = 0;
  real hydraulic_radius;
  real conveyance;

  ChlXSProps xsp = xsp_new ();

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
  real d1;
  real d2;

  /* distances for perimeter */
  real dy;
  real dz;

  real y1;
  real z1;

  real y2;
  real z2;

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
  conveyance =
      chl_const_manning () / ss->n * area * pow (hydraulic_radius, 2.0 / 3.0);

  xsp_set (xsp, XS_AREA, area);
  xsp_set (xsp, XS_TOP_WIDTH, top_width);
  xsp_set (xsp, XS_WETTED_PERIMETER, perimeter);
  xsp_set (xsp, XS_HYDRAULIC_RADIUS, hydraulic_radius);
  xsp_set (xsp, XS_CONVEYANCE, conveyance);

  if (sa)
    chl_xs_array_free (sa);

  return xsp;
}

/* area */
int
chl_xs_subsect_area (ChlXSSubsect ss, real y, real *area)
{
  if (ss == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "subsection is NULL", __FILE__, __LINE__);
      return -1;
    }

  if (area == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "area points to NULL", __FILE__, __LINE__);
      return -1;
    }

  ChlXSProps xsp = subsection_properties (ss, y);
  *area          = chl_xs_props_get (xsp, XS_AREA);
  chl_xs_props_free (xsp);

  return 0;
}

/* wetted perimeter */
int
chl_xs_subsect_wp (ChlXSSubsect ss, real y, real *wp)
{
  if (ss == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "subsection is NULL", __FILE__, __LINE__);
      return -1;
    }

  if (wp == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "wp points to NULL", __FILE__, __LINE__);
      return -1;
    }

  ChlXSProps xsp = subsection_properties (ss, y);
  *wp            = chl_xs_props_get (xsp, XS_WETTED_PERIMETER);
  chl_xs_props_free (xsp);

  return 0;
}

/* top width */
int
chl_xs_subsect_tw (ChlXSSubsect ss, real y, real *tw)
{
  if (ss == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "subsection is NULL", __FILE__, __LINE__);
      return -1;
    }

  if (tw == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "tw points to NULL", __FILE__, __LINE__);
      return -1;
    }

  ChlXSProps xsp = subsection_properties (ss, y);
  *tw            = chl_xs_props_get (xsp, XS_TOP_WIDTH);
  chl_xs_props_free (xsp);

  return 0;
}

/* hydraulic radius */
int
chl_xs_subsect_hr (ChlXSSubsect ss, real y, real *hr)
{
  if (ss == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "subsection is NULL", __FILE__, __LINE__);
      return -1;
    }

  if (hr == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "hr points to NULL", __FILE__, __LINE__);
      return -1;
    }

  ChlXSProps xsp = subsection_properties (ss, y);
  *hr            = chl_xs_props_get (xsp, XS_HYDRAULIC_RADIUS);
  chl_xs_props_free (xsp);

  return 0;
}

/* conveyance */
int
chl_xs_subsect_conv (ChlXSSubsect ss, real y, real *conv)
{
  if (ss == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "subsection is NULL", __FILE__, __LINE__);
      return -1;
    }

  if (conv == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "conv points to NULL", __FILE__, __LINE__);
      return -1;
    }

  ChlXSProps xsp = subsection_properties (ss, y);
  *conv          = chl_xs_props_get (xsp, XS_CONVEYANCE);
  chl_xs_props_free (xsp);

  return 0;
}
