#include <stdio.h>
#include <stdlib.h>

#include <chl/yaml.h>

int
main (void)
{

  const char *path = "EX1.RM0.2.yaml";
  FILE       *geom_fp;

  if ((geom_fp = fopen (path, "r")) == NULL)
    {
      fprintf (stderr, "Unable to open file: %s\n", path);
      return EXIT_FAILURE;
    }

  ChXSDefinition xs_def;

  if (!ch_yaml_parse_xs_file (geom_fp, &xs_def))
    goto error;

  if (fclose (geom_fp) == EOF)
    {
      fprintf (stderr, "Unable to close file: %s\n", path);
    }

  if (!ch_yaml_emit_xs_file (stdout, &xs_def))
    goto error;

  return 0;

error:

  if (fclose (geom_fp) == EOF)
    {
      fprintf (stderr, "Unable to close file: %s\n", path);
    }

  return 1;
}
