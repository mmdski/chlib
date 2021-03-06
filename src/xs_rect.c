#include <math.h>
#include <stdlib.h>

#include <chl/chl_constants.h>
#include <chl/chl_error.h>
#include <chl/chl_xs.h>

#include "error.h"
#include "memory.h"

#define FILENAME "xs_rect.c"

// creates a new rectangular cross section
ChlXSRect
chl_xs_rect_new (double width)
{

#ifdef CHECK_ARGS
  if (width <= 0)
    RAISE_ARG_ERR_NULL;
#endif

  ChlXSRect xs;
  NEW (xs);

  xs->width     = width;
  xs->roughness = 0;

  return xs;
}

// frees a rectangular cross section
int
chl_xs_rect_free (ChlXSRect xs)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  FREE (xs);

  return 0;
}

// returns the area
int
chl_xs_rect_area (ChlXSRect xs, double y, double *area)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  *area = xs->width * y;

  return 0;
}

// wetted perimeter
int
chl_xs_rect_wp (ChlXSRect xs, double y, double *wp)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  *wp = 2 * y + xs->width;

  return 0;
}

int
chl_xs_rect_tw (ChlXSRect xs, double y, double *tw)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  // silence unused variable warning
  (void) y;

  *tw = xs->width;

  return 0;
}

int
chl_xs_rect_hr (ChlXSRect xs, double y, double *hr)
{

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  *hr = (y * xs->width) / (2 * y + xs->width);

  return 0;
}

int
chl_xs_rect_props (void *xs, double y, ChlXSProps *xsp_ptr)
{

  ChlXSRect xs_rect = (ChlXSRect) xs;

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
#endif

  if (*xsp_ptr == NULL)
    *xsp_ptr = chl_xs_props_new ();

  ChlXSProps xsp = *xsp_ptr;

  double area             = xs_rect->width * y;
  double top_width        = xs_rect->width;
  double wetted_perimeter = 2 * y + xs_rect->width;
  double hydraulic_depth  = y;
  double hydraulic_radius = area / wetted_perimeter;
  double conveyance       = chl_const_manning () / xs_rect->roughness *
                      pow (hydraulic_radius, 2. / 3.) * area;
  double velocity_coeff = 1;
  double critical_flow  = area * sqrt (chl_const_gravity () * y);

  chl_xs_props_set (xsp, XS_DEPTH, y);
  chl_xs_props_set (xsp, XS_TOP_WIDTH, top_width);
  chl_xs_props_set (xsp, XS_WETTED_PERIMETER, wetted_perimeter);
  chl_xs_props_set (xsp, XS_HYDRAULIC_DEPTH, hydraulic_depth);
  chl_xs_props_set (xsp, XS_HYDRAULIC_RADIUS, hydraulic_radius);
  chl_xs_props_set (xsp, XS_CONVEYANCE, conveyance);
  chl_xs_props_set (xsp, XS_VELOCITY_COEFF, velocity_coeff);
  chl_xs_props_set (xsp, XS_CRITICAL_FLOW, critical_flow);

  return 0;
}

int
chl_xs_rect_spec_energy (void *xs, double y, double q, double *spec_energy)
{
  ChlXSRect xs_rect = (ChlXSRect) xs;

#ifdef CHECK_ARGS
  if (xs == NULL)
    RAISE_NULL_ERR_INT;
  if (spec_energy == NULL)
    RAISE_NULL_ERR_INT;
#endif

  double width = xs_rect->width;

  *spec_energy =
      y + q * q / (2. * chl_const_gravity () * y * y * width * width);

  return 0;
}
