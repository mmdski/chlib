add_chlib_test(memory-leak)
set_tests_properties(memory-leak PROPERTIES WILL_FAIL True)

add_chlib_test(double-free)
set_tests_properties(double-free PROPERTIES WILL_FAIL True)

add_chlib_test(access-after-free)
set_tests_properties(access-after-free PROPERTIES WILL_FAIL True)

add_chlib_test(no-leak)
