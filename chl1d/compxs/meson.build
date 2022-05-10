chl1dcompxs_inc = include_directories('.')

compxs_sources = [
  'array.c',
  'compound.c',
  'coordinate.c',
  'properties.c',
  'subsection.c'
]

chl1dcompxs = static_library('chl1dcompxs',
    compxs_sources,
    include_directories : [chl_inc, util_inc, chl1dcompxs_inc],
    link_with : chlutil)

if get_option('tests')
    subdir('tests')
endif
