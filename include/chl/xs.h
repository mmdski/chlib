#ifndef CHL_XS_
#define CHL_XS_

#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
  double station;
  double elevation;
} ChXSCoordinate;

typedef struct ChXSCoords ChXSCoords;

extern ChXSCoords     *ch_xs_coords_new (size_t length);
extern void            ch_xs_coords_init (ChXSCoords *coords,
                                          size_t      length,
                                          double     *station,
                                          double     *elevation);
extern void            ch_xs_coords_free (ChXSCoords **coords);
extern size_t          chl_xs_coords_length (ChXSCoords *coords);
extern ChXSCoordinate  ch_xs_coords_get (ChXSCoords *coords, size_t i);
extern ChXSCoordinate *ch_xs_coords_get_ptr (ChXSCoords *coords, size_t i);
extern void
ch_xs_coords_set (ChXSCoords *coords, ChXSCoordinate coord, size_t i);

#endif
