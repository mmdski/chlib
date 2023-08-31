message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler ID: ${CMAKE_C_COMPILER_ID}")

# determine if ASan is available
try_compile(ASAN_AVAILABLE "${CMAKE_BINARY_DIR}"
  SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test_mem-no-leak.c"
  CMAKE_FLAGS "-fsanitize=address"
  LINK_OPTIONS "-fsanitize=address"
  COPY_FILE "${CMAKE_BINARY_DIR}/lsan-check/no-leak")
message(STATUS "ASan available: ${ASAN_AVAILABLE}")

# determine if LSan is available with ASan
set(LSAN_AVAILABLE FALSE)

if(ASAN_AVAILABLE)
  file(COPY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/lsan-check.sh" "${CMAKE_BINARY_DIR}/lsan-check/lsan-check.sh")
  set(ENV{SOURCE_DIR} ${CMAKE_SOURCE_DIR})

  execute_process(COMMAND
    "${CMAKE_BINARY_DIR}/lsan-check/lsan-check.sh"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/lsan-check"
    RESULT_VARIABLE LSAN_CHECK_RESULT
    OUTPUT_QUIET ERROR_QUIET)

  if(LSAN_CHECK_RESULT STREQUAL "0")
    set(LSAN_AVAILABLE TRUE)
  endif()
endif()

message(STATUS "ASan+LSan available: ${LSAN_AVAILABLE}")

# determine if UBSan is available
try_compile(UBSAN_AVAILABLE "${CMAKE_BINARY_DIR}"
  SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test_mem-no-leak.c"
  CMAKE_FLAGS "-fsanitize=undefined"
  LINK_OPTIONS "-fsanitize=undefined")
message(STATUS "UBSan available: ${UBSAN_AVAILABLE}")

# determine if MSan is available
try_compile(MSAN_AVAILABLE "${CMAKE_BINARY_DIR}"
  SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test_mem-no-leak.c"
  CMAKE_FLAGS "-fsanitize=memory"
  LINK_OPTIONS "-fsanitize=memory")
message(STATUS "MSan available: ${MSAN_AVAILABLE}")

# -fno-sanitize-recover=all is necessary for UBSAN test failure
add_compile_options(-Wall -Wextra -pedantic -Werror -fno-sanitize-recover=all)

if(ASAN_AVAILABLE)
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
endif()

if(UBSAN_AVAILABLE)
  add_compile_options(-fsanitize=undefined)
  add_link_options(-fsanitize=undefined)
endif()

# add test environment variables
set(TEST_ENV "")

if(ASAN_AVAILABLE)
  if(LSAN_AVAILABLE)
    set(ASAN_OPTIONS "ASAN_OPTIONS=detect_leaks=1:abort_on_error=0")
    set(LSAN_OPTIONS "LSAN_OPTIONS=suppressions=${CMAKE_SOURCE_DIR}/lsan.supp")
    string(CONCAT TEST_ENV "${TEST_ENV}" "${ASAN_OPTIONS};${LSAN_OPTIONS}")
  else()
    string(CONCAT TEST_ENV "${TEST_ENV}" "ASAN_OPTIONS=abort_on_error=0")
  endif()
endif()

if(UBSAN_AVAILABLE)
  string(CONCAT TEST_ENV "${TEST_ENV};" "UBSAN_OPTIONS=print_stacktrace=1")
endif()

macro(add_chlib_test basename)
  add_chlib_exe(${basename} ${basename}.c)
  add_test(NAME ${basename} COMMAND ${basename})
  set_tests_properties(${basename} PROPERTIES ENVIRONMENT "${TEST_ENV}")
endmacro()

# these should fail if ASan is used
add_chlib_test(test_mem-access-after-free)
set_tests_properties(test_mem-access-after-free PROPERTIES WILL_FAIL TRUE)

add_chlib_test(test_mem-double-free)
set_tests_properties(test_mem-double-free PROPERTIES WILL_FAIL TRUE)

# this should fail if LSan is used
add_chlib_test(test_mem-leak)
set_tests_properties(test_mem-leak PROPERTIES WILL_FAIL TRUE)

# this should fail if UBSan is used
# adding -fno-sanitize-recover=all is necessary
add_chlib_test(ub-test)
set_tests_properties(ub-test PROPERTIES WILL_FAIL TRUE)

# this should not fail
add_chlib_test(test_mem-no-leak)
