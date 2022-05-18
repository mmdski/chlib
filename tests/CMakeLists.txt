set(ASAN True)
set(LSAN False)

# Windows compiler
if(MSVC)
  # add ASAN flag https://docs.microsoft.com/en-us/cpp/sanitizers/asan
  add_compile_options(/fsanitize=address)
  set(ASAN_AVAIL True)
  set(LSAN_AVAIL False)

# macOS
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
  # assume Homebrew Clang and has ASAN and LSAN
  if(("${CMAKE_C_COMPILER_ID}" STREQUAL "Clang"))
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
    set(ASAN_AVAIL True)
    set(LSAN_AVAIL True)

  # Apple Clang has ASAN but not LSAN
  elseif(("${CMAKE_C_COMPILER_ID}" STREQUAL "AppleClang"))
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
    set(ASAN_AVAIL True)
    set(LSAN_AVAIL (False AND LSAN))

  # assume everything else has neither
  else()
    set(ASAN_AVAIL False)
    set(LSAN_AVAIL False)
  endif()

# Linux
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
  set(ASAN_AVAIL True)
  set(LSAN_AVAIL True)

# unknown, assume no
else()
  set(ASAN_AVAIL False)
  set(LSAN_AVAIL False)

endif()

if(ASAN AND ASAN_AVAIL)
  set(USING_ASAN True)
  message(STATUS "Using ASAN")
endif()

if(USING_ASAN AND (LSAN AND LSAN_AVAIL))
  set(USING_LSAN True)
  message(STATUS "Using LSAN")
endif()

macro(add_chlib_test basename)

  add_chlib_exe(${basename} ${basename}.c)

  if(USING_ASAN)

    add_test(NAME ${basename} COMMAND ${basename})

    # detect leaks when using LSAN
    if(USING_LSAN)
      set_tests_properties(${basename} PROPERTIES ENVIRONMENT
      "ASAN_OPTIONS=detect_leaks=1:abort_on_error=0;LSAN_OPTIONS=suppressions=${CMAKE_SOURCE_DIR}/lsan.supp")
    else()
      set_tests_properties(${basename} PROPERTIES ENVIRONMENT
        "ASAN_OPTIONS=abort_on_error=0")
    endif()

  else()

    add_test(NAME ${basename} COMMAND ${basename})

  endif()

endmacro()

if(USING_ASAN)

  add_chlib_test(test_mem-access-after-free)
  add_chlib_test(test_mem-double-free)

  set_tests_properties(test_mem-access-after-free test_mem-double-free
    PROPERTIES WILL_FAIL True)

  add_chlib_test(test_mem-no-leak)

  if(USING_LSAN)
    add_chlib_test(test_mem-leak)
    set_tests_properties(test_mem-leak PROPERTIES WILL_FAIL true)
  endif()

if(CHECK_ARGS)
  add_chlib_test(test_check_args)
endif()

endif(USING_ASAN)

add_chlib_test(test_constants)
add_chlib_test(test_error)
add_chlib_test(test_exit)
add_chlib_test(test_reach)
add_chlib_test(test_string)
add_chlib_test(test_xs_array)
add_chlib_test(test_xs_comp)
add_chlib_test(test_xs_rect)
add_chlib_test(test_xs_subsect)
