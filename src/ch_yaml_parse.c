
#include <assert.h>
#include <stdbool.h>

#include <yaml.h>

#include <chl/xs.h>

#include "ch_yaml.h"

int
ch_yaml_parse_xs_coords (yaml_parser_t *parser, ChXSCoords *xs_coords)
{
  assert (parser);
  assert (xs_coords);

  int done = 0;

  yaml_event_type_t type;
  yaml_event_t      event;

  bool in_length    = false;
  bool in_station   = false;
  bool in_elevation = false;

  char  *scalar_value;
  size_t sq_idx = 0;

  while (!done)
    {

      CH_YAML_PARSER_PARSE

      type = event.type;

      switch (type)
        {
        case YAML_STREAM_END_EVENT:
          done = 1;
          break;
        case YAML_MAPPING_START_EVENT:
          break;
        case YAML_MAPPING_END_EVENT:
          done = 1;
          break;
        case YAML_SEQUENCE_START_EVENT:
          sq_idx = 0;
          break;
        case YAML_SEQUENCE_END_EVENT:
          in_station   = false;
          in_elevation = false;
          break;
        case YAML_SCALAR_EVENT:
          if (sq_idx >= CH_XS_MAX_COORDS)
            {
              fputs ("Maximum number of coordinates exceeded\n", stderr);
              goto error;
            }

          scalar_value = (char *) event.data.scalar.value;

          if (strncmp ("length", scalar_value, CH_MAX_SCALAR_CHAR) == 0)
            in_length = true;
          else if (strncmp ("station", scalar_value, CH_MAX_SCALAR_CHAR) == 0)
            in_station = true;
          else if (strncmp ("elevation", scalar_value, CH_MAX_SCALAR_CHAR) == 0)
            in_elevation = true;
          else if (in_length)
            {
              xs_coords->length = (int) strtol (scalar_value, NULL, 10);
              in_length         = false; // coordinate length is only one scalar
            }
          else if (in_station)
            xs_coords->station[sq_idx++] = strtod (scalar_value, NULL);
          else if (in_elevation)
            xs_coords->elevation[sq_idx++] = strtod (scalar_value, NULL);
        default:
          break;
        }

      yaml_event_delete (&event);
    }

  return 1;

error:
  yaml_event_delete (&event);
  return 0;
}

int
ch_yaml_parse_xs_roughness (yaml_parser_t *parser, ChXSRoughness *xs_roughness)
{
  assert (parser);
  assert (xs_roughness);

  int done = 0;

  yaml_event_type_t type;
  yaml_event_t      event;

  bool in_length  = false;
  bool in_station = false;
  bool in_value   = false;

  char  *scalar_value;
  size_t sq_idx = 0;

  while (!done)
    {

      CH_YAML_PARSER_PARSE

      type = event.type;

      switch (type)
        {
        case YAML_STREAM_END_EVENT:
          done = 1;
          break;
        case YAML_MAPPING_START_EVENT:
          break;
        case YAML_MAPPING_END_EVENT:
          done = 1;
          break;
        case YAML_SEQUENCE_START_EVENT:
          sq_idx = 0;
          break;
        case YAML_SEQUENCE_END_EVENT:
          in_station = false;
          in_value   = false;
          break;
        case YAML_SCALAR_EVENT:
          if (sq_idx >= CH_XS_MAX_COORDS)
            {
              fputs ("Maximum number of coordinates exceeded\n", stderr);
              goto error;
            }

          scalar_value = (char *) event.data.scalar.value;

          if (strncmp ("length", scalar_value, CH_MAX_SCALAR_CHAR) == 0)
            in_length = true;
          else if (strncmp ("station", scalar_value, CH_MAX_SCALAR_CHAR) == 0)
            in_station = true;
          else if (strncmp ("value", scalar_value, CH_MAX_SCALAR_CHAR) == 0)
            in_value = true;
          else if (in_length)
            {
              xs_roughness->length = (int) strtol (scalar_value, NULL, 10);
              in_length            = false; // length is only one scalar
            }
          else if (in_station)
            xs_roughness->station[sq_idx++] = strtod (scalar_value, NULL);
          else if (in_value)
            xs_roughness->value[sq_idx++] = strtod (scalar_value, NULL);
        default:
          break;
        }

      yaml_event_delete (&event);
    }

  return 1;

error:
  yaml_event_delete (&event);
  return 0;
}

int
ch_yaml_parse_xs (yaml_parser_t *parser, ChXSDefinition *xs_def)
{

  assert (parser);
  assert (xs_def);

  int done = 0;

  yaml_event_type_t type;
  yaml_event_t      event;

  char  *scalar_value;
  size_t sq_idx = 0;

  bool in_bank_sta = false;

  while (!done)
    {
      CH_YAML_PARSER_PARSE

      type = event.type;

      switch (type)
        {
        case YAML_STREAM_START_EVENT:
          break;
        case YAML_STREAM_END_EVENT:
          done = 1;
          break;
        case YAML_DOCUMENT_START_EVENT:
          break;
        case YAML_DOCUMENT_END_EVENT:
          break;
        case YAML_MAPPING_START_EVENT:
          break;
        case YAML_MAPPING_END_EVENT:
          break;
        case YAML_SEQUENCE_START_EVENT:
          sq_idx = 0;
          break;
        case YAML_SEQUENCE_END_EVENT:
          in_bank_sta = false;
          break;
        case YAML_SCALAR_EVENT:

          scalar_value = (char *) event.data.scalar.value;

          if (strncmp ("coordinates", scalar_value, CH_MAX_SCALAR_CHAR) == 0)
            {
              if (!ch_yaml_parse_xs_coords (parser, &(xs_def->coordinates)))
                goto error;
            }
          else if (strncmp ("roughness", scalar_value, CH_MAX_SCALAR_CHAR) == 0)
            {
              if (!ch_yaml_parse_xs_roughness (parser, &(xs_def->roughness)))
                goto error;
            }
          else if (strncmp (
                       "bank_stations", scalar_value, CH_MAX_SCALAR_CHAR) == 0)
            {
              in_bank_sta = true;
            }

          else if (in_bank_sta)
            {
              if (sq_idx >= 2)
                {
                  fputs ("Max. number of bank stations exceeded", stderr);
                  goto error;
                }
              xs_def->bank_stations[sq_idx++] = strtod (scalar_value, NULL);
            }
          break;
        default:
          break;
        }

      yaml_event_delete (&event);
    }

  return 1;

error:
  yaml_event_delete (&event);
  return 0;
}

int
ch_yaml_parse_xs_file (FILE *fp, ChXSDefinition *xs_def)
{

  assert (fp);
  assert (xs_def);

  yaml_parser_t parser;
  if (!yaml_parser_initialize (&parser))
    {
      fputs ("Unable to initialize yaml parser", stderr);
      goto error;
    }

  yaml_parser_set_input_file (&parser, fp);

  if (!ch_yaml_parse_xs (&parser, xs_def))
    {
      goto error;
    }

  yaml_parser_delete (&parser);

  return 1;

error:
  return 0;
}
