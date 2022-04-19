chl_sys_sources = files(
    [
        'constants.c',
        'error.c',
        'list.c',
        'memory.c',
        'string.c'
    ]
)
chlib_c_args = ['-DCHL_COMPILATION']

chl_inc = include_directories('.')

subdir('xsection')

chlsys = static_library('chl_sys',
    chl_sys_sources,
    include_directories : inc,
    c_args : chlib_c_args)

chlib = static_library('chlib',
    link_whole : [chlsys, chlxsection])
