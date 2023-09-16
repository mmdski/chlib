#include <gtest/gtest.h>

extern "C"
{
#include <string.h>

#include <yaml.h>

#include <chl/xs.h>
#include <chl/yaml.h>
}

namespace
{
TEST (ch_yaml_parse, xs)
{
  const char *yaml_xs = "coordinates:\n"
                        " length: 8\n"
                        " station: [ 210, 220, 260, 265, 270, 275, 300, 310 ]\n"
                        " elevation: [ 90, 82, 80, 70, 71, 81, 83, 91 ]\n"
                        "roughness:\n"
                        " length: 3\n"
                        " station: [ 210, 260, 275 ]\n"
                        " value: [ 0.07, 0.04, 0.07 ]\n"
                        "bank_stations: [ 260, 275 ]\n";
  size_t      length  = strlen (yaml_xs);

  yaml_parser_t parser;
  yaml_parser_initialize (&parser);
  yaml_parser_set_input_string (
      &parser, (const unsigned char *) yaml_xs, length);

  ChXSDefinition xs_def_parsed;

  ChXSDefinition xs_def = { { 260, 275 },
                            { 8,
                              { 210, 220, 260, 265, 270, 275, 300, 310 },
                              { 90, 82, 80, 70, 71, 81, 83, 91 } },
                            { 3, { 210, 260, 275 }, { 0.07, 0.04, 0.07 } } };

  ASSERT_EQ (ch_yaml_parse_xs (&parser, &xs_def_parsed), 0);

  ASSERT_EQ (xs_def.bank_stations[0], xs_def_parsed.bank_stations[0]);
  ASSERT_EQ (xs_def.bank_stations[1], xs_def_parsed.bank_stations[1]);
  ASSERT_EQ (xs_def.coordinates.length, xs_def_parsed.coordinates.length);
  for (size_t i = 0; i < xs_def.coordinates.length; i++)
    {
      ASSERT_EQ (xs_def.coordinates.station[i],
                 xs_def_parsed.coordinates.station[i]);
      ASSERT_EQ (xs_def.coordinates.elevation[i],
                 xs_def_parsed.coordinates.elevation[i]);
    }
  ASSERT_EQ (xs_def.roughness.length, xs_def_parsed.roughness.length);
  for (size_t i = 0; i < xs_def.roughness.length; i++)
    {
      ASSERT_EQ (xs_def.roughness.station[i],
                 xs_def_parsed.roughness.station[i]);
      ASSERT_EQ (xs_def.roughness.value[i], xs_def_parsed.roughness.value[i]);
    }

  yaml_parser_delete (&parser);
}
}

int
main (int argc, char **argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
