#ifndef CHL_YAML_H_
#define CHL_YAML_H_

#define CH_MAX_RAS_IO_CHARS 83

#include <stdio.h>

#include <yaml.h>

#include <chl/xs.h>

extern int ch_io_ras_xs_def (FILE *geom_fp, ChXSDefinition *xs_definition);

extern int ch_yaml_parse_xs (yaml_parser_t *parser, ChXSDefinition *xs_def);

extern int ch_yaml_parse_xs_coords (yaml_parser_t *parser,
                                    ChXSCoords    *xs_coords);

extern int ch_yaml_parse_xs_roughness (yaml_parser_t *parser,
                                       ChXSRoughness *xs_roughness);

#endif
