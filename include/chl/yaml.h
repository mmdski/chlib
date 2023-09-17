#ifndef CHL_YAML_H_
#define CHL_YAML_H_

#define CH_MAX_RAS_IO_CHARS 83

#include <stdio.h>

#include <yaml.h>

#include <chl/xs.h>

extern int ch_yaml_parse_xs_file (FILE *fp, ChXSDefinition *xs_def);

extern int ch_yaml_emit_xs_file (FILE *fp, ChXSDefinition *xs_def);

#endif
