#ifndef CHL_XS_
#define CHL_XS_

#include <stdbool.h>
#include <stdlib.h>

#define CH_XS_MAX_COORDS 500

typedef struct
{
  size_t length;
  double station[CH_XS_MAX_COORDS];
  double elevation[CH_XS_MAX_COORDS];
} ChXSCoords;

typedef struct
{
  size_t length;
  double station[CH_XS_MAX_COORDS];
  double value[CH_XS_MAX_COORDS];
} ChXSRoughness;

typedef struct
{
  double        bank_stations[2];
  ChXSCoords    coordinates;
  ChXSRoughness roughness;
} ChXSDefinition;

ChXSDefinition *ch_xs_def_new (void);
void            ch_xs_def_free (ChXSDefinition *xs_def);

#endif
