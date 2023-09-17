#include <assert.h>

#include <yaml.h>

#include <chl/xs.h>

#include "ch_yaml.h"

int
ch_yaml_emit_xs (yaml_emitter_t *emitter, ChXSDefinition *xs_def)
{

  assert (emitter);
  assert (xs_def);

  yaml_event_t event;

  // begin cross section
  if (!ch_yaml_emit_mapping_start (emitter, &event))
    goto error;

  // begin coordinates
  if (!ch_yaml_emit_scalar_str (emitter, &event, "coordinates"))
    goto error;

  // begin coordinate mapping
  if (!ch_yaml_emit_mapping_start (emitter, &event))
    goto error;

  if (!ch_yaml_emit_scalar_str (emitter, &event, "length"))
    goto error;

  if (!ch_yaml_emit_scalar_len (emitter, &event, xs_def->coordinates.length))
    goto error;

  if (!ch_yaml_emit_scalar_str (emitter, &event, "station"))
    goto error;
  if (!ch_yaml_emit_seq_dbl (emitter,
                             &event,
                             xs_def->coordinates.length,
                             xs_def->coordinates.station))
    goto error;

  if (!ch_yaml_emit_scalar_str (emitter, &event, "elevation"))
    goto error;
  if (!ch_yaml_emit_seq_dbl (emitter,
                             &event,
                             xs_def->coordinates.length,
                             xs_def->coordinates.elevation))
    goto error;

  // end coordinates mapping
  if (!ch_yaml_emit_mapping_end (emitter, &event))
    goto error;

  if (!ch_yaml_emit_scalar_str (emitter, &event, "roughness"))
    goto error;

  // begin roughness mapping
  if (!ch_yaml_emit_mapping_start (emitter, &event))
    goto error;

  if (!ch_yaml_emit_scalar_str (emitter, &event, "length"))
    goto error;

  if (!ch_yaml_emit_scalar_len (emitter, &event, xs_def->roughness.length))
    goto error;

  if (!ch_yaml_emit_scalar_str (emitter, &event, "station"))
    goto error;
  if (!ch_yaml_emit_seq_dbl (
          emitter, &event, xs_def->roughness.length, xs_def->roughness.station))
    goto error;

  if (!ch_yaml_emit_scalar_str (emitter, &event, "value"))
    goto error;
  if (!ch_yaml_emit_seq_dbl (
          emitter, &event, xs_def->roughness.length, xs_def->roughness.value))
    goto error;

  // end roughness mapping
  if (!ch_yaml_emit_mapping_end (emitter, &event))
    goto error;

  if (!ch_yaml_emit_scalar_str (emitter, &event, "bank_stations"))
    goto error;
  if (!ch_yaml_emit_seq_dbl (emitter, &event, 2, xs_def->bank_stations))
    goto error;

  // end cross section
  if (!ch_yaml_emit_mapping_end (emitter, &event))
    goto error;

  return 1;

error:
  return 0;
}

static int
emit_xs_stream (yaml_emitter_t *emitter, ChXSDefinition *xs_def)
{
  assert (emitter);
  assert (xs_def);

  yaml_event_t event;

  if (!yaml_stream_start_event_initialize (&event, YAML_UTF8_ENCODING))
    goto error;
  if (!yaml_emitter_emit (emitter, &event))
    goto error;

  if (!yaml_document_start_event_initialize (
          &event, NULL, NULL, NULL, CH_YAML_IMPLICIT))
    goto error;
  if (!yaml_emitter_emit (emitter, &event))
    goto error;

  if (!ch_yaml_emit_xs (emitter, xs_def))
    goto error;

  if (!yaml_document_end_event_initialize (&event, CH_YAML_IMPLICIT))
    goto error;
  if (!yaml_emitter_emit (emitter, &event))
    goto error;

  if (!yaml_stream_end_event_initialize (&event))
    goto error;
  if (!yaml_emitter_emit (emitter, &event))
    goto error;
  return 1;

error:
  return 0;
}

int
ch_yaml_emit_xs_file (FILE *fp, ChXSDefinition *xs_def)
{

  assert (fp);
  assert (xs_def);

  yaml_emitter_t emitter;

  if (!yaml_emitter_initialize (&emitter))
    {
      fputs ("Unable to initialize yaml emitter", stderr);
      goto error;
    }

  yaml_emitter_set_output_file (&emitter, fp);

  if (!emit_xs_stream (&emitter, xs_def))
    goto error;

  yaml_emitter_delete (&emitter);
  return 1;

error:
  yaml_emitter_delete (&emitter);
  return 0;
}

size_t
ch_yaml_emit_xs_string (const char *output, size_t size, ChXSDefinition *xs_def)
{
  assert (output);
  assert (xs_def);

  yaml_emitter_t emitter;

  if (!yaml_emitter_initialize (&emitter))
    {
      fputs ("Unable to initialize yaml emitter", stderr);
      goto error;
    }

  size_t size_written;
  yaml_emitter_set_output_string (
      &emitter, (unsigned char *) output, size, &size_written);

  if (!emit_xs_stream (&emitter, xs_def))
    goto error;

  yaml_emitter_delete (&emitter);

  return size_written;

error:
  yaml_emitter_delete (&emitter);
  return 0;
}
