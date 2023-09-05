#include <stdlib.h>

#include "ch_xs_coords.h"

ChXSCoords *
ch_xs_coords_new (size_t size)
{

  ChXSCoords *coords = malloc (sizeof (ChXSCoords) + sizeof (double) * size);

  if (!coords)
    return NULL;

  coords->size   = size;
  coords->length = 0;

  return coords;
}

void
ch_xs_coords_free (ChXSCoords **coords)
{

  if (!(coords) || !(*coords))
    return;

  free (*coords);

  return;
}

void
ch_xs_coords_init (ChXSCoords *coords,
                   size_t      length,
                   double     *station,
                   double     *elevation)
{

  assert (coords);
  assert (length <= coords->size);

  coords->length = length;

  for (size_t i = 0; i < length; i++)
    {
      coords->coords[i].station   = station[i];
      coords->coords[i].elevation = elevation[i];
    }
}

size_t
chl_xs_coords_length (ChXSCoords *coords)
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
