# add_subdirectory(xs)

add_library(chlib ch_xs_coords.c)

if(TESTS)
  add_executable(ch_xs_coords.test ch_xs_coords.test.cpp)
  target_link_libraries(ch_xs_coords.test chlib GTest::gtest GTest::gtest_main)
  gtest_add_tests(TARGET ch_xs_coords.test TEST_LIST ch_xs_coords.test-list)
  set_tests_properties(${ch_xs_coords.test-list} PROPERTIES ENVIRONMENT "${TEST_ENV}")
endif()
