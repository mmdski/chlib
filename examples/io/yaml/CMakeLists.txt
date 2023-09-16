file(COPY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/EX1.RM0.2.yaml" "${CMAKE_CURRENT_BINARY_DIR}/EX1.RM0.2.yaml")

add_executable(ex_io_yaml_xs_coords xs_coords.c)
target_link_libraries(ex_io_yaml_xs_coords chlib)
