if(MEM_TESTS)

  macro(add_chlib_test basename)
    add_chlib_exe(${basename})
    add_test(NAME ${basename} COMMAND ${basename})
    set_tests_properties(${basename} PROPERTIES ENVIRONMENT
      "ASAN_OPTIONS=detect_leaks=1:abort_on_error=0;LSAN_OPTIONS=suppressions=${CMAKE_SOURCE_DIR}/lsan.supp")
  endmacro()

  add_subdirectory(memory)

else()

  macro(add_chlib_test basename)
    add_chlib_exe(${basename})
    add_test(NAME ${basename} COMMAND ${basename})
  endmacro()

endif()

if(CHECK_ARGS)
  add_chlib_test(test_check_args)
endif()

add_chlib_test(constants)
add_chlib_test(test_error)
add_chlib_test(test_exit)
add_chlib_test(test_reach)
add_chlib_test(test_string)
add_chlib_test(test_xs_array)
add_chlib_test(test_xs_comp)
add_chlib_test(test_xs_rect)
add_chlib_test(test_xs_subsect)
