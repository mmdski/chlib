#ifndef CHL_YAML_H_
#define CHL_YAML_H_

#include <stdio.h>

#include <yaml.h>

#include <chl/xs.h>

extern int ch_yaml_parse_xs_file (FILE *fp, ChXSDefinition *xs_def);

extern int ch_yaml_parse_xs_string (const char *input, ChXSDefinition *xs_def);

extern int ch_yaml_emit_xs_file (FILE *fp, ChXSDefinition *xs_def);

extern size_t ch_yaml_emit_xs_string (const char     *output,
                                      size_t          size,
                                      ChXSDefinition *xs_def);

#endif
