cmake_minimum_required(VERSION 3.18)

project(chlib)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(MSVC)
  add_compile_options(/guard:cf /analyze /permissive- /W4 /WX)

else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)

  if(COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
  endif()
endif()

if(TESTS)
  enable_testing()
endif()

include_directories(include)

macro(add_chlib_exe basename)
  add_executable(${basename} ${basename}.c)
  target_link_libraries(${basename} PRIVATE chlib)
endmacro()

if(TESTS)
  add_subdirectory(test)
endif()
