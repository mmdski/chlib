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
  ChXSDefinition xs_def_parsed;

  ChXSDefinition xs_def = { { 260, 275 },
                            { 8,
                              { 210, 220, 260, 265, 270, 275, 300, 310 },
                              { 90, 82, 80, 70, 71, 81, 83, 91 } },
                            { 3, { 210, 260, 275 }, { 0.07, 0.04, 0.07 } } };

  FILE *fp = fopen ("ch_yaml_xs.yaml", "r");
  ASSERT_TRUE (ch_yaml_parse_xs_file (fp, &xs_def_parsed));

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

  ASSERT_TRUE (fclose (fp) != EOF);
}
}

int
main (int argc, char **argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
