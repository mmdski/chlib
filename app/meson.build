error = executable('error',
    'error.c',
    include_directories : [inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
real = executable('real',
    'real.c',
    include_directories : [inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
string = executable('string',
    'string.c',
    include_directories : [inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)

subdir('errorstack')
