#include <gtest/gtest.h>
extern "C"
{
#include <stdio.h>
#include <string.h>

#include <yaml.h>

#include <chl/xs.h>
#include <chl/yaml.h>
}

namespace
{
TEST (ch_yaml_emit, xs_file)
{
  const char *yaml_xs = "coordinates:\n"
                        "  length: 8\n"
                        "  station: [210, 220, 260, 265, 270, 275, 300, 310]\n"
                        "  elevation: [90, 82, 80, 70, 71, 81, 83, 91]\n"
                        "roughness:\n"
                        "  length: 3\n"
                        "  station: [210, 260, 275]\n"
                        "  value: [0.07, 0.04, 0.07]\n"
                        "bank_stations: [260, 275]\n";

  size_t         size = strlen (yaml_xs);
  char           buffer[500];
  FILE          *buff_fp = fmemopen (buffer, 500, "w");
  ChXSDefinition xs_def  = { { 260, 275 },
                             { 8,
                               { 210, 220, 260, 265, 270, 275, 300, 310 },
                               { 90, 82, 80, 70, 71, 81, 83, 91 } },
                             { 3, { 210, 260, 275 }, { 0.07, 0.04, 0.07 } } };
  ASSERT_TRUE (ch_yaml_emit_xs_file (buff_fp, &xs_def));

  fclose (buff_fp);
  ASSERT_EQ (strncmp (yaml_xs, buffer, size), 0);
}

TEST (ch_yaml_emit, xs_string)
{
  const char *yaml_xs = "coordinates:\n"
                        "  length: 8\n"
                        "  station: [210, 220, 260, 265, 270, 275, 300, 310]\n"
                        "  elevation: [90, 82, 80, 70, 71, 81, 83, 91]\n"
                        "roughness:\n"
                        "  length: 3\n"
                        "  station: [210, 260, 275]\n"
                        "  value: [0.07, 0.04, 0.07]\n"
                        "bank_stations: [260, 275]\n";

  ChXSDefinition xs_def = { { 260, 275 },
                            { 8,
                              { 210, 220, 260, 265, 270, 275, 300, 310 },
                              { 90, 82, 80, 70, 71, 81, 83, 91 } },
                            { 3, { 210, 260, 275 }, { 0.07, 0.04, 0.07 } } };

  char   write_buffer[500];
  size_t size         = strlen (yaml_xs);
  size_t size_written = ch_yaml_emit_xs_string (write_buffer, 500, &xs_def);

  ASSERT_EQ (size, size_written);
  ASSERT_EQ (strncmp (yaml_xs, write_buffer, size), 0);
}
}

int
main (int argc, char **argv)
{
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
