chl1d_inc = include_directories('.')

subdir('compxs')

chl1d_sources = [
  'rectxs.c'
  ]

chl1d = static_library('chl1d',
    chl1d_sources,
    include_directories : [chl_inc, util_inc],
    link_with : [chlutil],
    link_whole : [chl1dcompxs])

if get_option('tests')
    subdir('tests')
endif
