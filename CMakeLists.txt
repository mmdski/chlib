cmake_minimum_required(VERSION 3.18)

project(chlib)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(MSVC)
  add_compile_options(/guard:cf /analyze /permissive- /W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

if(TESTS)
  message(STATUS "Adding tests")
  add_compile_definitions(TESTING)
  if (NOT MSVC)
    message(STATUS "Adding sanitize address compile and link options")
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
  endif()
endif()

if(COVERAGE)
  add_compile_options(--coverage)
  add_link_options(--coverage)
endif()

if(CHECK_ARGS)
  add_compile_definitions(CHECK_ARGS)
endif()

include_directories(include)

add_subdirectory(src)

macro(add_chlib_exe basename)
  add_executable(${basename} ${basename}.c)
  target_link_libraries(${basename} PRIVATE chlib)
endmacro()

if (APP)
  add_subdirectory(app)
endif()

if(TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
