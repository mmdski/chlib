if(ASAN)
  add_subdirectory(san)
endif()

add_executable(ch_yaml_parse.test ch_yaml_parse.test.cpp)
target_link_libraries(ch_yaml_parse.test chlib GTest::gtest GTest::gtest_main)
gtest_add_tests(TARGET ch_yaml_parse.test TEST_LIST ch_yaml_parse.test-list)
set_tests_properties(${ch_yaml_parse.test-list} PROPERTIES ENVIRONMENT "${TEST_ENV}")
