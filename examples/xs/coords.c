#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <chl/io.h>
#include <chl/xs.h>

int
main (void)
{

  const char *path = "EX1.RM0.2.g01";
  // const char *path = "BEAVCREK.RM5.61.g01";
  FILE *geom_file;

  if ((geom_file = fopen (path, "r")) == NULL)
    {
      fprintf (stderr, "Unable to open file: %s\n", path);
      return EXIT_FAILURE;
    }

  ChXSDefinition *xs_definition = malloc (sizeof (ChXSDefinition));

  if (ch_io_ras_xs_def (geom_file, xs_definition) < 0)
    goto fail;

  puts ("Coordinates:");
  for (size_t i = 0; i < xs_definition->n_coordinates; i++)
    {
      printf ("%2lu%10lg%10lg\n",
              i,
              xs_definition->station[i],
              xs_definition->elevation[i]);
    }

  puts ("Manning's:");
  for (size_t i = 0; i < xs_definition->n_mann; i++)
    {
      printf ("%2lu%10lg%10lg\n",
              i,
              xs_definition->mann_station[i],
              xs_definition->mann_value[i]);
    }

  puts ("Bank Stations:");
  printf ("%lg, %lg\n",
          xs_definition->bank_stations[0],
          xs_definition->bank_stations[1]);

fail:
  free (xs_definition);
  if (fclose (geom_file) == EOF)
    fputs ("Failed to close file\n", stderr);
  return EXIT_SUCCESS;
}
