#include <stdio.h>
#include <string.h>

#include <yaml.h>

void print_escaped (yaml_char_t *str, size_t length);

int
main (void)
{
  int         exit_status = EXIT_SUCCESS;
  const char *yaml_xs     = "coordinates:\n"
                            " length: 8\n"
                            " station: [ 210, 220, 260, 265, 270, 275, 300, 310 ]\n"
                            " elevation: [ 90, 82, 80, 70, 71, 81, 83, 91 ]\n"
                            "roughness:\n"
                            " length: 3\n"
                            " station: [ 210, 260, 275 ]\n"
                            " value: [ 0.07, 0.04, 0.07 ]\n"
                            "bank_stations: [ 260, 275 ]\n";
  size_t      length      = strlen (yaml_xs);

  yaml_parser_t parser;

  if (!yaml_parser_initialize (&parser))
    {
      fputs ("Unable to initialize yaml parser", stderr);
      exit_status = EXIT_FAILURE;
      goto error;
    }

  yaml_parser_set_input_string (
      &parser, (const unsigned char *) yaml_xs, length);

  int               done = 0;
  yaml_event_t      event;
  yaml_event_type_t type;

  while (!done)
    {
      if (!yaml_parser_parse (&parser, &event))
        {
          if (parser.problem_mark.line || parser.problem_mark.column)
            {
              fprintf (stderr,
                       "Parse error: %s\nLine: %lu Column: %lu\n",
                       parser.problem,
                       (unsigned long) parser.problem_mark.line + 1,
                       (unsigned long) parser.problem_mark.column + 1);
            }
          else
            {
              fprintf (stderr, "Parse error: %s\n", parser.problem);
            }
          goto error;
        }

      type = event.type;

      switch (type)
        {
        case YAML_NO_EVENT:
          printf ("???\n");
          break;
        case YAML_STREAM_START_EVENT:
          printf ("+STR\n");
          break;
        case YAML_STREAM_END_EVENT:
          printf ("-STR\n");
          done = 1;
          break;
        case YAML_DOCUMENT_START_EVENT:
          printf ("+DOC\n");
          break;
        case YAML_DOCUMENT_END_EVENT:
          printf ("-DOC\n");
          break;
        case YAML_MAPPING_START_EVENT:
          printf ("+MAP\n");
          break;
        case YAML_MAPPING_END_EVENT:
          printf ("-MAP\n");
          break;
        case YAML_SEQUENCE_START_EVENT:
          printf ("+SEQ");
          if (event.data.sequence_start.style == YAML_FLOW_SEQUENCE_STYLE)
            printf (" []");
          printf ("\n");
          break;
        case YAML_SEQUENCE_END_EVENT:
          printf ("-SEQ\n");
          break;
        case YAML_SCALAR_EVENT:
          printf ("=VAL");
          switch (event.data.scalar.style)
            {
            case YAML_PLAIN_SCALAR_STYLE:
              printf (" :");
              break;
            case YAML_SINGLE_QUOTED_SCALAR_STYLE:
              printf (" '");
              break;
            case YAML_DOUBLE_QUOTED_SCALAR_STYLE:
              printf (" \"");
              break;
            case YAML_LITERAL_SCALAR_STYLE:
              printf (" |");
              break;
            case YAML_FOLDED_SCALAR_STYLE:
              printf (" >");
              break;
            case YAML_ANY_SCALAR_STYLE:
              abort ();
            }
          print_escaped (event.data.scalar.value, event.data.scalar.length);
          printf ("\n");
          break;
        case YAML_ALIAS_EVENT:
          printf ("=ALI *%s\n", event.data.alias.anchor);
          break;
        default:
          abort ();
          break;
        }

      yaml_event_delete (&event);
    }

error:

  yaml_parser_delete (&parser);
  return exit_status;
}

void
print_escaped (yaml_char_t *str, size_t length)
{
  size_t i;
  char   c;

  for (i = 0; i < length; i++)
    {
      c = *(str + i);
      if (c == '\\')
        printf ("\\\\");
      else if (c == '\0')
        printf ("\\0");
      else if (c == '\b')
        printf ("\\b");
      else if (c == '\n')
        printf ("\\n");
      else if (c == '\r')
        printf ("\\r");
      else if (c == '\t')
        printf ("\\t");
      else
        printf ("%c", c);
    }
}
