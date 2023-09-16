#ifndef CH_YAML_INT_H_
#define CH_YAML_INT_H_

#define CH_MAX_SCALAR_CHAR 50

#define CH_YAML_PARSER_PARSE                                                   \
  if (!yaml_parser_parse (parser, &event))                                     \
    {                                                                          \
      if (parser->problem_mark.line || parser->problem_mark.column)            \
        {                                                                      \
          fprintf (stderr,                                                     \
                   "Parse error: %s\nLine: %lu Column: %lu\n",                 \
                   parser->problem,                                            \
                   (unsigned long) parser->problem_mark.line + 1,              \
                   (unsigned long) parser->problem_mark.column + 1);           \
        }                                                                      \
      else                                                                     \
        {                                                                      \
          fprintf (stderr, "Parse error: %s\n", parser->problem);              \
        }                                                                      \
    }

#include <chl/yaml.h>

#endif
