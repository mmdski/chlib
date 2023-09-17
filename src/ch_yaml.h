#ifndef CH_YAML_INT_H_
#define CH_YAML_INT_H_

#define CH_MAX_SCALAR_CHAR 50

#define CH_YAML_IMPLICIT 1

#include <chl/yaml.h>

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
                                            YAML_ANY_MAPPING_STYLE))
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
ch_yaml_emit_scalar (yaml_emitter_t *emitter,
                     yaml_event_t   *event,
                     const char     *tag,
                     const char     *value)
{
  if (!yaml_scalar_event_initialize (event,
                                     NULL,
                                     (yaml_char_t *) tag,
                                     (yaml_char_t *) value,
                                     strlen (value),
                                     CH_YAML_IMPLICIT,
                                     CH_YAML_IMPLICIT,
                                     YAML_PLAIN_SCALAR_STYLE))
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
  return ch_yaml_emit_scalar (emitter, event, YAML_STR_TAG, value);
}

static inline int
ch_yaml_emit_scalar_len (yaml_emitter_t *emitter,
                         yaml_event_t   *event,
                         size_t          value)
{
  snprintf (buffer, CH_YAML_STATIC_BUFFER_LEN, "%lu", value);
  return ch_yaml_emit_scalar (emitter, event, YAML_INT_TAG, buffer);
}

static inline int
ch_yaml_emit_scalar_dbl (yaml_emitter_t *emitter,
                         yaml_event_t   *event,
                         double          value)
{
  snprintf (buffer, CH_YAML_STATIC_BUFFER_LEN, "%.8g", value);
  return ch_yaml_emit_scalar (emitter, event, YAML_FLOAT_TAG, buffer);
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
                                             YAML_FLOW_SEQUENCE_STYLE))
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
