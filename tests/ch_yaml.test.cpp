#include <gtest/gtest.h>

extern "C"
{
#include <chl/xs.h>
#include <chl/yaml.h>
}

namespace
{
TEST (ch_yaml, xs)
{

  ChXSDefinition *xs_def_parsed_p = ch_xs_def_new ();

  ChXSDefinition xs_def = { { 260, 275 },
                            { 8,
                              { 210, 220, 260, 265, 270, 275, 300, 310 },
                              { 90, 82, 80, 70, 71, 81, 83, 91 } },
                            { 3, { 210, 260, 275 }, { 0.07, 0.04, 0.07 } } };

  char *buffer = new char[500];

  for (size_t i = 0; i < 500; i++)
    buffer[i] = '\0';

  ch_yaml_emit_xs_string (buffer, 500, &xs_def);
  ch_yaml_parse_xs_string (buffer, xs_def_parsed_p);

  ASSERT_EQ (xs_def.bank_stations[0], xs_def_parsed_p->bank_stations[0]);
  ASSERT_EQ (xs_def.bank_stations[1], xs_def_parsed_p->bank_stations[1]);
  ASSERT_EQ (xs_def.coordinates.length, xs_def_parsed_p->coordinates.length);
  for (size_t i = 0; i < xs_def.coordinates.length; i++)
    {
      ASSERT_EQ (xs_def.coordinates.station[i],
                 xs_def_parsed_p->coordinates.station[i]);
      ASSERT_EQ (xs_def.coordinates.elevation[i],
                 xs_def_parsed_p->coordinates.elevation[i]);
    }
  ASSERT_EQ (xs_def.roughness.length, xs_def_parsed_p->roughness.length);
  for (size_t i = 0; i < xs_def.roughness.length; i++)
    {
      ASSERT_EQ (xs_def.roughness.station[i],
                 xs_def_parsed_p->roughness.station[i]);
      ASSERT_EQ (xs_def.roughness.value[i],
                 xs_def_parsed_p->roughness.value[i]);
    }

  delete[] buffer;
  ch_xs_def_free (xs_def_parsed_p);
}
}

int
main (int argc, char **argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
