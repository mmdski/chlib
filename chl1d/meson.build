chl1d_inc = include_directories('.')

chl1d_sources = [
  'rectxs.c'
  ]

chl1d = static_library('chl1d',
    chl1d_sources,
    include_directories : [chl_inc, util_inc],
    link_with : [chlutil])

if get_option('build_tests')
    subdir('tests')
endif
