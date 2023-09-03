
add_executable(no-leak no-leak.c)
add_test(NAME san.no-leak COMMAND no-leak)
set_tests_properties(san.no-leak
  PROPERTIES
  ENVIRONMENT "${TEST_ENV}")

add_executable(access-after-free access-after-free.c)
add_test(NAME san.access-after-free COMMAND access-after-free)
set_tests_properties(san.access-after-free
  PROPERTIES
  ENVIRONMENT "${TEST_ENV}"
  WILL_FAIL TRUE)

add_executable(leak leak.c)
add_test(NAME san.leak COMMAND leak)
set_tests_properties(san.leak
  PROPERTIES
  ENVIRONMENT "${TEST_ENV}"
  WILL_FAIL TRUE)

add_executable(double-free double-free.c)
add_test(NAME san.double-free COMMAND double-free)
set_tests_properties(san.double-free
  PROPERTIES
  ENVIRONMENT "${TEST_ENV}"
  WILL_FAIL TRUE)

add_executable(ub-test ub-test.c)
add_test(NAME san.ub-test COMMAND ub-test)
set_tests_properties(san.ub-test
  PROPERTIES
  ENVIRONMENT "${TEST_ENV}"
  WILL_FAIL TRUE)
