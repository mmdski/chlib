# find_package(Gnuplot REQUIRED TRUE)

file(COPY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/EX1.RM0.2.g01" "${CMAKE_CURRENT_BINARY_DIR}/EX1.RM0.2.g01")
file(COPY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/BEAVCREK.RM5.61.g01" "${CMAKE_CURRENT_BINARY_DIR}/BEAVCREK.RM5.61.g01")
add_executable(coords coords.c)
target_link_libraries(coords chlib)
