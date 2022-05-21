add_library(chlib
  error.c
  exit.c
  list.c
  memory.c
  reach.c
  string.c
  xs_array.c
  xs_compound.c
  xs_coordinate.c
  xs_properties.c
  xs_rect.c
  xs_subsection.c
)
if(NOT MSVC)
  target_link_libraries(chlib PRIVATE m)
endif()
