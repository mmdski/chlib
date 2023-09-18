#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <chl/yaml.h>

int
main (void)
{
  const char *yaml_xs = "coordinates:\n"
                        "  length: 8\n"
                        "  station: [210, 220, 260, 265, 270, 275, 300, 310]\n"
                        "  elevation: [90, 82, 80, 70, 71, 81, 83, 91]\n"
                        "roughness:\n"
                        "  length: 3\n"
                        "  station: [210, 260, 275]\n"
                        "  value: [0.07, 0.04, 0.07]\n"
                        "bank_stations: [260, 275]\n";

  ChXSDefinition xs_def;

  if (!ch_yaml_parse_xs_string (yaml_xs, &xs_def))
    goto error;

  char   buffer[500];
  size_t size_written = ch_yaml_emit_xs_string (buffer, 500, &xs_def);
  if (!size_written)
    goto error;

  printf ("%s", buffer);

  return 0;

error:

  return 1;
}
