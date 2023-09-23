if(ASAN)
  add_subdirectory(san)
endif()

add_executable(ch_yaml.test ch_yaml.test.cpp)
target_link_libraries(ch_yaml.test chlib GTest::gtest GTest::gtest_main)
gtest_add_tests(TARGET ch_yaml.test TEST_LIST ch_yaml.test-list)
set_tests_properties(${ch_yaml.test-list} PROPERTIES ENVIRONMENT "${TEST_ENV}")
