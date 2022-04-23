#include <chl.h>
#include <math.h>
#include <stdlib.h>

#include "array.h"
#include "coordinate.h"
#include "error.h"
#include "memory.h"
#include "properties.h"
#include "subsection.h"

/*
 * cross section interface
 */
struct ChlXSCompound
{
  int           n_coordinates; /* number of coordinates */
  int           n_subsections; /* number of subsections */
  ChlXSArray    ca;            /* coordinate array */
  ChlXSSubsect *ss;            /* array of subsections */
};

ChlXSProps
calc_hydraulic_properties (ChlXSCompound xs, real h)
{

  if (xs == NULL)
    RAISE_NULL_ERR_NULL;

  int n_subsections = xs->n_subsections;
  int i;

  real g = chl_const_gravity ();

  real area        = 0; /* area */
  real area_ss     = 0; /* subsection area */
  real top_width   = 0; /* top width */
  real w_perimeter = 0; /* wetted perimeter */
  real h_depth;         /* hydraulic depth */
  real h_radius;        /* hydraulic radius */
  real conveyance = 0;  /* conveyance */
  real k_ss       = 0;  /* subsection conveyance */
  real sum        = 0;  /* sum for velocity coefficient */
  real alpha;           /* velocity coefficient */
  real crit_flow;       /* critical flow */

  ChlXSProps   xsp = xsp_new ();
  ChlXSProps   xsp_ss;
  ChlXSSubsect ss;

  for (i = 0; i < n_subsections; i++)
    {

      /* skip subsection if depth is less than the lowest point in the
       * subsection */
      ss = *(xs->ss + i);

      xsp_ss  = subsection_properties (ss, h);
      area_ss = xsp_get (xsp_ss, XS_AREA);
      k_ss    = xsp_get (xsp_ss, XS_CONVEYANCE);
      top_width += xsp_get (xsp_ss, XS_TOP_WIDTH);
      w_perimeter += xsp_get (xsp_ss, XS_WETTED_PERIMETER);

      if (area_ss > 0)
        {
          sum += (k_ss * k_ss * k_ss) / (area_ss * area_ss);
        }

      xsp_free (xsp_ss);

      area += area_ss;
      conveyance += k_ss;
    }

  h_depth  = area / top_width;
  h_radius = area / w_perimeter;
  if (isnan (h_radius))
    conveyance = NAN;
  alpha     = (area * area) * sum / (conveyance * conveyance * conveyance);
  crit_flow = area * sqrt (g * h_depth);

  xsp_set (xsp, XS_DEPTH, h);
  xsp_set (xsp, XS_AREA, area);
  xsp_set (xsp, XS_TOP_WIDTH, top_width);
  xsp_set (xsp, XS_WETTED_PERIMETER, w_perimeter);
  xsp_set (xsp, XS_HYDRAULIC_DEPTH, h_depth);
  xsp_set (xsp, XS_HYDRAULIC_RADIUS, h_radius);
  xsp_set (xsp, XS_CONVEYANCE, conveyance);
  xsp_set (xsp, XS_VELOCITY_COEFF, alpha);
  xsp_set (xsp, XS_CRITICAL_FLOW, crit_flow);

  return xsp;
}

ChlXSCompound
chl_xs_comp_new (int   n_coords,
                 real *y,
                 real *z,
                 int   n_roughness,
                 real *roughness,
                 real *z_roughness)
{
  if (n_coords < 2)
    RAISE_ARG_ERR_NULL;

  if (!y || !z)
    RAISE_NULL_ERR_NULL;

  if (n_roughness < 1)
    RAISE_ARG_ERR_NULL;

  if (roughness == NULL)
    RAISE_NULL_ERR_NULL;

  if (n_roughness > 1)
    if (z_roughness == NULL)
      RAISE_NULL_ERR_NULL;

  for (int i = 0; i < n_roughness; i++)
    if (roughness[i] <= 0)
      RAISE_ARG_ERR_NULL;

  ChlXSArray ca = chl_xs_array_new (n_coords, y, z);
  if (ca == NULL)
    {
      chl_err_stack_push (__FILE__, __LINE__);
      return NULL;
    }

  Coordinate c;

  /* cross section to return */
  ChlXSCompound xs;
  NEW (xs);
  xs->n_coordinates = chl_xs_array_length (ca);
  xs->n_subsections = n_roughness;
  xs->ss            = chl_calloc (n_roughness, sizeof (ChlXSSubsect));
  xs->ca            = ca;

  /* initialize z splits
   * include first and last z-values of the CoArray
   */
  real *z_splits = chl_calloc (n_roughness + 1, sizeof (real));

  c           = chl_xs_array_get (xs->ca, 0);
  z_splits[0] = c->z;
  coord_free (c);

  c = chl_xs_array_get (xs->ca, chl_xs_array_length (xs->ca) - 1);
  z_splits[n_roughness] = c->z;
  coord_free (c);

  for (int i = 1; i < n_roughness; i++)
    {
      z_splits[i] = *(z_roughness + i - 1);
    }

  /* create subsections from the roughness section breaks */
  ChlXSArray subarray;
  for (int i = 0; i < n_roughness; i++)
    {
      subarray = chl_xs_array_subarray (xs->ca, z_splits[i], z_splits[i + 1]);
      *(xs->ss + i) = chl_xs_subsect_new (subarray, *(roughness + i));
      chl_xs_array_free (subarray);
    }

  chl_free (z_splits);

  return xs;
}

void
chl_xs_comp_free (ChlXSCompound xs)
{
  if (!xs)
    return;

  int i;
  int n = xs->n_subsections;

  /* free the coordinate array */
  chl_xs_array_free (xs->ca);

  /* free the subsections and subsection array */
  for (i = 0; i < n; i++)
    {
      chl_xs_subsect_free (*(xs->ss + i));
    }

  chl_free (xs->ss);

  FREE (xs);
}
