#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__
#include <chl.h>

/**
 * xs_prop:
 * @XS_DEPTH:             Cross section depth of computed properties
 * @XS_AREA:              Cross section area
 * @XS_TOP_WIDTH:         Top width
 * @XS_WETTED_PERIMETER:  Wetted perimeter
 * @XS_HYDRAULIC_DEPTH:   Hydraulic depth
 * @XS_HYDRAULIC_RADIUS:  Hydraulic radius
 * @XS_CONVEYANCE:        Conveyance
 * @XS_VELOCITY_COEFF:    Velocity coefficient
 * @XS_CRITICAL_FLOW:     Critical flow
 * @N_XSP:                Number of hydraulic properties
 */
typedef enum
{
  XS_DEPTH,
  XS_AREA,
  XS_TOP_WIDTH,
  XS_WETTED_PERIMETER,
  XS_HYDRAULIC_DEPTH,
  XS_HYDRAULIC_RADIUS,
  XS_CONVEYANCE,
  XS_VELOCITY_COEFF,
  XS_CRITICAL_FLOW,
  N_XSP
} xs_prop;

typedef struct ChlXSProps *ChlXSProps;

extern ChlXSProps xsp_new (void);

extern void xsp_free (ChlXSProps xsp);

extern real xsp_get (ChlXSProps xsp, xs_prop prop);

extern void xsp_set (ChlXSProps xsp, xs_prop prop, real value);

#endif
