cmake_minimum_required(VERSION 3.18)

project(chlib)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
  add_compile_options(/guard:cf /analyze /permissive- /W4 /WX)

else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)

  if(COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
  endif()
endif()

include_directories(include)

if(TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
  )

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  enable_testing()
  include(GoogleTest)

  set(TEST_ENV "")
  set(GTEST_ENV "")

  if(ASAN)
    add_compile_options(-fno-omit-frame-pointer)

    # for ASan and LSan
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)

    # for UBSan
    add_compile_options(-fsanitize=undefined -fno-sanitize-recover=all)
    add_link_options(-fsanitize=undefined)

    set(ASAN_OPTIONS "ASAN_OPTIONS=detect_leaks=1:abort_on_error=0")
    set(LSAN_OPTIONS "LSAN_OPTIONS=suppressions=${CMAKE_SOURCE_DIR}/lsan.supp")
    set(UBSAN_OPTIONS "UBSAN_OPTIONS=print_stacktrace=1")

    string(CONCAT TEST_ENV "${TEST_ENV}" "${ASAN_OPTIONS};${LSAN_OPTIONS};${UBSAN_OPTIONS}")
  endif()
endif()

add_subdirectory(src)

add_subdirectory(tests)
