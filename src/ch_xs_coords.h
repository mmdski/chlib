#ifndef CH_XS_COORDS_H_
#define CH_XS_COORDS_H_

#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include <chl/xs.h>

static inline bool
chl_xs_coordinate_is_close (ChXSCoordinate a,
                            ChXSCoordinate b,
                            double         atol,
                            double         rtol)
{
  bool sta_close =
      fabs (a.station - b.station) <= (atol + rtol * fabs (b.station));

  bool ele_close =
      fabs (a.elevation - b.elevation) <= (atol + rtol * fabs (b.elevation));

  return sta_close && ele_close;
}

static inline bool
chl_xs_coordinate_eq (ChXSCoordinate a, ChXSCoordinate b)
{
  if ((a.station == b.station) && (a.elevation == b.elevation))
    return true;
  else
    return false;
}

#endif
