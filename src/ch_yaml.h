#ifndef CH_YAML_INT_H_
#define CH_YAML_INT_H_

#define CH_MAX_SCALAR_CHAR 50

#define CH_YAML_IMPLICIT 1
#define CH_YAML_MAPPING_STYLE YAML_FLOW_MAPPING_STYLE
#define CH_YAML_SEQUENCE_STYLE YAML_FLOW_SEQUENCE_STYLE

#include <chl/yaml.h>

#include "ch_io.h"

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

#define CH_YAML_STATIC_BUFFER_LEN 100
static char buffer[CH_YAML_STATIC_BUFFER_LEN];

static inline int
ch_yaml_emit_mapping_start (yaml_emitter_t *emitter, yaml_event_t *event)
{
  if (!yaml_mapping_start_event_initialize (event,
                                            NULL,
                                            (yaml_char_t *) YAML_MAP_TAG,
                                            CH_YAML_IMPLICIT,
                                            CH_YAML_MAPPING_STYLE))
    goto error;
  if (!yaml_emitter_emit (emitter, event))
    goto error;
  return 1;
error:
  return 0;
}

static inline int
ch_yaml_emit_mapping_end (yaml_emitter_t *emitter, yaml_event_t *event)
{
  if (!yaml_mapping_end_event_initialize (event))
    goto error;
  if (!yaml_emitter_emit (emitter, event))
    goto error;
  return 1;
error:
  return 0;
}

static inline int
ch_yaml_emit_scalar (yaml_emitter_t     *emitter,
                     yaml_event_t       *event,
                     const char         *tag,
                     const char         *value,
                     yaml_scalar_style_t style)
{
  if (!yaml_scalar_event_initialize (event,
                                     NULL,
                                     (yaml_char_t *) tag,
                                     (yaml_char_t *) value,
                                     (int) strlen (value),
                                     CH_YAML_IMPLICIT,
                                     CH_YAML_IMPLICIT,
                                     style))
    goto error;
  if (!yaml_emitter_emit (emitter, event))
    goto error;
  return 1;
error:
  return 0;
}

static inline int
ch_yaml_emit_scalar_str (yaml_emitter_t *emitter,
                         yaml_event_t   *event,
                         const char     *value)
{
  return ch_yaml_emit_scalar (
      emitter, event, YAML_STR_TAG, value, YAML_DOUBLE_QUOTED_SCALAR_STYLE);
}

static inline int
ch_yaml_emit_scalar_len (yaml_emitter_t *emitter,
                         yaml_event_t   *event,
                         size_t          value)
{
  ch_snprintf (buffer, CH_YAML_STATIC_BUFFER_LEN, SIZE_T_FMT, value);

  return ch_yaml_emit_scalar (
      emitter, event, YAML_INT_TAG, buffer, YAML_PLAIN_SCALAR_STYLE);
}

static inline int
ch_yaml_emit_scalar_dbl (yaml_emitter_t *emitter,
                         yaml_event_t   *event,
                         double          value)
{
  ch_snprintf (buffer, CH_YAML_STATIC_BUFFER_LEN, "%.8g", value);
  return ch_yaml_emit_scalar (
      emitter, event, YAML_FLOAT_TAG, buffer, YAML_PLAIN_SCALAR_STYLE);
}

static inline int
ch_yaml_emit_seq_dbl (yaml_emitter_t *emitter,
                      yaml_event_t   *event,
                      size_t          length,
                      double         *values)
{
  if (!yaml_sequence_start_event_initialize (event,
                                             NULL,
                                             (yaml_char_t *) YAML_SEQ_TAG,
                                             CH_YAML_IMPLICIT,
                                             CH_YAML_SEQUENCE_STYLE))
    goto error;
  if (!yaml_emitter_emit (emitter, event))
    goto error;

  for (size_t i = 0; i < length; i++)
    {
      if (!ch_yaml_emit_scalar_dbl (emitter, event, values[i]))
        goto error;
    }

  if (!yaml_sequence_end_event_initialize (event))
    goto error;
  if (!yaml_emitter_emit (emitter, event))
    goto error;

  return 1;
error:
  return 0;
}

#endif
