#ifndef CH_XS_SUBSECT_H_
#define CH_XS_SUBSECT_H_

#include <chl/xs.h>

#include "ch_xs_coords.h"

struct ChXSSubsect
{
  double      min_elevation;
  ChXSCoords *coordinates;
};

#endif
