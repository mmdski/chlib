file(COPY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/EX1.RM0.2.yaml" "${CMAKE_CURRENT_BINARY_DIR}/EX1.RM0.2.yaml")

add_executable(ex_yaml yaml.c)
target_link_libraries(ex_yaml yaml)

add_executable(ex_yaml_string yaml_string.c)
target_link_libraries(ex_yaml_string yaml)

add_executable(ex_yaml_xs xs.c)
target_link_libraries(ex_yaml_xs chlib)

# add_executable(ex_yaml_xs_coords xs_coords.c)
# target_link_libraries(ex_yaml_xs_coords chlib)
