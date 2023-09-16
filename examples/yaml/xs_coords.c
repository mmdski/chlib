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

  ChXSCoords xs_coords;

  xs_coords.length = 0;
  if (ch_yaml_parse_xs_coords (&parser, &xs_coords))
    {
      exit_status = EXIT_FAILURE;
      goto error;
    }

  for (size_t i = 0; i < xs_coords.length; i++)
    {
      printf ("station: %5.f, elevation: %5.f\n",
              xs_coords.station[i],
              xs_coords.elevation[i]);
    }

error:
  if (fclose (geom_fp) == EOF)
    {
      fprintf (stderr, "Unable to close file: %s\n", path);
      exit_status = EXIT_FAILURE;
    }

  yaml_parser_delete (&parser);
  return exit_status;
}
