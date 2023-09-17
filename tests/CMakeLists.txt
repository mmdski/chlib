if(ASAN)
  add_subdirectory(san)
endif()

file(COPY_FILE
  "${CMAKE_CURRENT_SOURCE_DIR}/ch_yaml_xs.yaml"
  "${CMAKE_CURRENT_BINARY_DIR}/ch_yaml_xs.yaml")

add_executable(ch_yaml_parse.test ch_yaml_parse.test.cpp)
target_link_libraries(ch_yaml_parse.test chlib yaml GTest::gtest GTest::gtest_main)
gtest_add_tests(TARGET ch_yaml_parse.test TEST_LIST ch_yaml_parse.test-list)
set_tests_properties(${ch_yaml_parse.test-list} PROPERTIES ENVIRONMENT "${TEST_ENV}")

add_executable(ch_yaml_emit.test ch_yaml_emit.test.cpp)
target_link_libraries(ch_yaml_emit.test chlib yaml GTest::gtest GTest::gtest_main)
gtest_add_tests(TARGET ch_yaml_emit.test TEST_LIST ch_yaml_emit.test-list)
set_tests_properties(${ch_yaml_emit.test-list} PROPERTIES ENVIRONMENT "${TEST_ENV}")
