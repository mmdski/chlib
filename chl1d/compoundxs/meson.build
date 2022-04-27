chlcompoundxs_inc = include_directories('.')

compoundxs_sources = [
  'array.c',
  'compound.c',
  'coordinate.c',
  'properties.c',
  'subsection.c'
]

chlcompoundxs = static_library('chlcompoundxs',
    compoundxs_sources,
    include_directories : [chl_inc, util_inc, chlcompoundxs_inc],
    link_with : chl_util)
