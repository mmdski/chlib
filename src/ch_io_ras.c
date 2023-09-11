#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <chl/io.h>
#include <chl/xs.h>

int
ch_io_ras_xs_def (FILE *geom_fp, ChXSDefinition *xs_definition)
{
  assert (geom_fp);
  assert (xs_definition);

  char line_of_file[CH_MAX_RAS_IO_CHARS];

  int n;

  size_t n_coords;

  n = fscanf (geom_fp, "#Sta/Elev=%2lu", &n_coords);
  if (n != 1)
    goto fail;

  assert (n_coords > 0 && n_coords <= CH_XS_MAX_COORDS);

  xs_definition->n_coordinates = n_coords;

  // read in the cross section station, elevation values
  for (size_t i = 0; i < n_coords; i++)
    {
      n = fscanf (geom_fp,
                  "%8lg%8lg",
                  &xs_definition->station[i],
                  &xs_definition->elevation[i]);
      // must read in two doubles (sta, ele)
      if (n < 2)
        goto fail;
    }

  // read to the end of the line
  fgets (line_of_file, 83, geom_fp);

  // read in the number of manning's n points
  size_t n_manning;
  n = fscanf (geom_fp, "#Mann= %lu , %*i , %*i", &n_manning);
  if (n != 1)
    goto fail;

  xs_definition->n_mann = n_manning;

  fgets (line_of_file, 83, geom_fp);

  for (size_t i = 0; i < n_manning; i++)
    {
      n = fscanf (geom_fp,
                  "%8lg%8lg%*8lg",
                  &xs_definition->mann_station[i],
                  &xs_definition->mann_value[i]);
      if (n != 2)
        goto fail;
    }

  // read to end of line
  fgets (line_of_file, 83, geom_fp);

  n = fscanf (geom_fp,
              "Bank Sta=%lg,%lg",
              &xs_definition->bank_stations[0],
              &xs_definition->bank_stations[1]);
  if (n != 2)
    goto fail;

  // read to end of line
  fgets (line_of_file, 83, geom_fp);

  goto success;

fail:
  return -1;

success:
  return 0;
}
