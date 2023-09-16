#include <stdlib.h>

#include <chl/yaml.h>

int
main (void)
{

  int         exit_status = EXIT_SUCCESS;
  const char *path        = "EX1.RM0.2.yaml";
  FILE       *geom_fp;

  yaml_parser_t parser;

  if ((geom_fp = fopen (path, "r")) == NULL)
    {
      fprintf (stderr, "Unable to open file: %s\n", path);
      return EXIT_FAILURE;
    }

  if (!yaml_parser_initialize (&parser))
    {
      fputs ("Unable to initialize yaml parser", stderr);
      exit_status = EXIT_FAILURE;
      goto error;
    }

  yaml_parser_set_input_file (&parser, geom_fp);

  ChXSDefinition xs_def;

  xs_def.coordinates.length = 0;
  xs_def.roughness.length   = 0;

  if (ch_yaml_parse_xs (&parser, &xs_def))
    {
      exit_status = EXIT_FAILURE;
      goto error;
    }

  printf ("coordinates:\n");
  for (size_t i = 0; i < xs_def.coordinates.length; i++)
    {
      printf ("\tstation: %5.f, elevation: %5.f\n",
              xs_def.coordinates.station[i],
              xs_def.coordinates.elevation[i]);
    }

  printf ("roughness:\n");
  for (size_t i = 0; i < xs_def.roughness.length; i++)
    {
      printf ("\tstation: %5.f, value: %5.g\n",
              xs_def.roughness.station[i],
              xs_def.roughness.value[i]);
    }

  printf ("bank_stations:\n");
  printf ("\t%5.f, %5.f\n", xs_def.bank_stations[0], xs_def.bank_stations[1]);

error:
  if (fclose (geom_fp) == EOF)
    {
      fprintf (stderr, "Unable to close file: %s\n", path);
      exit_status = EXIT_FAILURE;
    }

  yaml_parser_delete (&parser);
  return exit_status;
}
