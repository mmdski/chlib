add_executable(coordinate.test coordinate.test.cpp)
target_link_libraries(coordinate.test GTest::gtest GTest::gtest_main)
gtest_add_tests(TARGET coordinate.test TEST_LIST coordinate.test-tests)
set_tests_properties(${coordinate.test-tests} PROPERTIES ENVIRONMENT ${GTEST_ENV})
