util_sources = [
  'constants.c',
  'error.c',
  'list.c',
  'memory.c',
  'string.c'
]

chlutil = static_library('chlutil',
    util_sources,
    include_directories : [chl_inc, util_inc],
    dependencies : m_dep)

if get_option('tests')
    subdir('tests')
endif
