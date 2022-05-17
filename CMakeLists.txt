cmake_minimum_required(VERSION 3.18)

project(chlib)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(MSVC)
  add_compile_options(/guard:cf /analyze /permissive- /W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# maybe find a more sophisticated way to determine if sanitize tests can be ran
if(NOT MSVC AND NOT EMSCRIPTEN)
  set(MEM_TESTS True)
endif()

if(TESTS)
  message(STATUS "Enabling testing")
  enable_testing()
  add_compile_definitions(TESTING)
  if(MEM_TESTS)
    message(STATUS "Adding sanitize address compile and link options")
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
  endif()
endif()

if(COVERAGE)
  add_compile_options(--coverage)
  add_link_options(--coverage)
endif()

# set check arguments
add_compile_definitions(CHECK_ARGS)

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
  add_subdirectory(tests)
endif()
