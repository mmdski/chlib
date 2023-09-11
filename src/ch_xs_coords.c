#include <stdlib.h>

#include "ch_xs_coords.h"

ChXSCoords *
ch_xs_coords_new (void)
{

  ChXSCoords *coords = malloc (sizeof (ChXSCoords));

  if (!coords)
    return NULL;

  coords->length = 0;
  coords->size   = CH_XS_MAX_COORDS;

  return coords;
}

ChXSCoords *
ch_xs_coords_init (size_t length, double *station, double *elevation)
{

  assert (station && elevation);
  assert (length != 0 && length <= CH_XS_MAX_COORDS);

  ChXSCoords *coords = ch_xs_coords_new ();
  if (!coords)
    return NULL;

  coords->length = length;

  // make sure station is in increasing order
  coords->coords[0].station   = station[0];
  coords->coords[0].elevation = elevation[0];

  for (size_t i = 1; i < length; i++)
    {
      coords->coords[i].station   = station[i];
      coords->coords[i].elevation = elevation[i];
      if (coords->coords[i - 1].station > coords->coords[i].station)
        goto fail_station;
    }

  return coords;

fail_station:
  ch_xs_coords_free (&coords);
  return NULL;
}

void
ch_xs_coords_free (ChXSCoords **coords)
{

  if (!(coords) || !(*coords))
    return;

  free (*coords);

  *coords = NULL;

  return;
}

size_t
ch_xs_coords_length (ChXSCoords *coords)
{
  assert (coords);
  return coords->length;
}

ChXSCoordinate
ch_xs_coords_get (ChXSCoords *array, size_t i)
{
  assert (array);
  assert (i < array->size);

  return array->coords[i];
}

ChXSCoordinate *
ch_xs_coords_get_ptr (ChXSCoords *array, size_t i)
{
  assert (array);
  assert (i < array->size);

  return &array->coords[i];
}

void
ch_xs_coords_set (ChXSCoords *array, ChXSCoordinate coord, size_t i)
{

  assert (array);
  assert (i < array->size);

  array->coords[i].station   = coord.station;
  array->coords[i].elevation = coord.elevation;
}
