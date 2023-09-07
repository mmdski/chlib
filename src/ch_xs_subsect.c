#include <assert.h>
#include <stdlib.h>

#include "ch_xs_coords.h"
#include "ch_xs_subsect.h"

ChXSSubsect *
ch_xs_subsect_init (size_t n_coords, double *station, double *elevation)
{
  assert (station && elevation);
  assert (n_coords);

  double min_elevation = elevation[0];

  // find the minimum elevation of the subsection
  for (size_t i = 1; i < n_coords; i++)
    {
      if (elevation[i] < min_elevation)
        min_elevation = elevation[i];
    }

  ChXSCoords *coords = ch_xs_coords_init (n_coords, station, elevation);
  if (!coords)
    return NULL;

  ChXSSubsect *subsect = malloc (sizeof (ChXSSubsect));
  if (!subsect)
    {
      ch_xs_coords_free (&coords);
      return NULL;
    }

  subsect->min_elevation = min_elevation;
  subsect->coordinates   = coords;

  return subsect;
}

void
ch_xs_subsect_free (ChXSSubsect **subsect)
{
  if (!(subsect) || !(*subsect))
    return;

  ch_xs_coords_free (&((*subsect)->coordinates));

  free (*subsect);
}
