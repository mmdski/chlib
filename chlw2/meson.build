chlw2_inc = include_directories('.')

chlw2_sources = [
  'grid.c'
]

chlw2 = static_library('chlw2',
  chlw2_sources,
  include_directories : [chl_inc, util_inc, chlw2_inc],
  link_with : [chlutil])

if get_option('tests')
    subdir('tests')
endif
