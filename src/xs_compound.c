#include <math.h>
#include <stdlib.h>

#include <chl/chl_constants.h>
#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "error.h"
#include "memory.h"
#include "xs_array.h"
#include "xs_coordinate.h"

/*
 * cross section interface
 */
struct _ChlXSComp
{
  int           n_coordinates; /* number of coordinates */
  int           n_subsections; /* number of subsections */
  ChlXSArray    ca;            /* coordinate array */
  ChlXSSubsect *ss;            /* array of subsections */
};

int
chl_xs_comp_props (ChlXSComp xs, double h, ChlXSProps *xsp_ptr)
{

  if (xs == NULL)
    RAISE_NULL_ERR_INT;

  bool xsp_created = false;

  if (*xsp_ptr == NULL)
    {
      *xsp_ptr    = chl_xs_props_new ();
      xsp_created = true;
    }

  int n_subsections = xs->n_subsections;
  int i;

  double g = chl_const_gravity ();

  double area        = 0; /* xs area */
  double top_width   = 0; /* xs top width */
  double w_perimeter = 0; /* wetted perimeter */
  double conveyance  = 0; /* conveyance */
  double sum         = 0; /* sum for velocity coefficient */
  double h_depth;         /* hydraulic depth */
  double h_radius;        /* hydraulic radius */

  double area_ss; /* subsection area */
  double tw_ss;   /* subsection top width */
  double wp_ss;   /* subsection wetted perimeter */
  double k_ss;    /* subsection conveyance */

  double alpha;     /* velocity coefficient */
  double crit_flow; /* critical flow */

  ChlXSProps   xsp    = *xsp_ptr;
  ChlXSProps   xsp_ss = NULL;
  ChlXSSubsect ss;

  for (i = 0; i < n_subsections; i++)
    {

      /* skip subsection if depth is less than the lowest point in the
       * subsection */
      ss = *(xs->ss + i);

      if (chl_xs_subsect_props (ss, h, &xsp_ss) < 0)
        {
          chl_err_stack_push (__FILE__, __LINE__);
          goto fail;
        }

      /* get the subsection area */
      if (chl_xs_props_get (xsp_ss, XS_AREA, &area_ss) < 0)
        {
          chl_err_stack_push (__FILE__, __LINE__);
          goto fail;
        }

      /* get the subsection conveyance */
      if (chl_xs_props_get (xsp_ss, XS_CONVEYANCE, &k_ss) < 0)
        {
          chl_err_stack_push (__FILE__, __LINE__);
          goto fail;
        }

      /* get the subsection top width and add it to the total top width */
      if (chl_xs_props_get (xsp_ss, XS_TOP_WIDTH, &tw_ss))
        {
          chl_err_stack_push (__FILE__, __LINE__);
          goto fail;
        }
      top_width += tw_ss;

      /* get the subsection wetted perimeter and add it to the total wetted
       * perimeter */
      if (chl_xs_props_get (xsp_ss, XS_WETTED_PERIMETER, &wp_ss))
        {
          chl_err_stack_push (__FILE__, __LINE__);
          goto fail;
        }
      w_perimeter += wp_ss;

      if (area_ss > 0)
        {
          sum += (k_ss * k_ss * k_ss) / (area_ss * area_ss);
        }

      area += area_ss;
      conveyance += k_ss;
    }

  chl_xs_props_free (xsp_ss);

  h_depth  = area / top_width;
  h_radius = area / w_perimeter;
  if (isnan (h_radius))
    conveyance = NAN;
  alpha     = (area * area) * sum / (conveyance * conveyance * conveyance);
  crit_flow = area * sqrt (g * h_depth);

  chl_xs_props_set (xsp, XS_DEPTH, h);
  chl_xs_props_set (xsp, XS_AREA, area);
  chl_xs_props_set (xsp, XS_TOP_WIDTH, top_width);
  chl_xs_props_set (xsp, XS_WETTED_PERIMETER, w_perimeter);
  chl_xs_props_set (xsp, XS_HYDRAULIC_DEPTH, h_depth);
  chl_xs_props_set (xsp, XS_HYDRAULIC_RADIUS, h_radius);
  chl_xs_props_set (xsp, XS_CONVEYANCE, conveyance);
  chl_xs_props_set (xsp, XS_VELOCITY_COEFF, alpha);
  chl_xs_props_set (xsp, XS_CRITICAL_FLOW, crit_flow);

  return 0;

fail:
  if (xsp_created)
    chl_xs_props_free (xsp);
  chl_xs_props_free (xsp_ss);
  return -1;
}

ChlXSComp
chl_xs_comp_new (int     n_coords,
                 double *y,
                 double *z,
                 int     n_roughness,
                 double *roughness,
                 double *z_roughness)
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
  ChlXSComp xs;
  NEW (xs);
  xs->n_coordinates = chl_xs_array_length (ca);
  xs->n_subsections = n_roughness;
  xs->ss            = chl_calloc (n_roughness, sizeof (ChlXSSubsect));
  xs->ca            = ca;

  /* initialize z splits
   * include first and last z-values of the array
   */
  double *z_splits = chl_calloc (n_roughness + 1, sizeof (double));

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
chl_xs_comp_free (ChlXSComp xs)
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
