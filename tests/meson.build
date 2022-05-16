# run memory tests if ASAN is enabled
if get_option('b_sanitize') == 'address'
    subdir('memory')
endif

if get_option('check_args')
    test_check_args = executable('test_check_args',
        'test_check_args.c',
        include_directories : chl_inc,
        link_with : chlib,
        name_suffix : exe_name_suffix)
    test('test_check_args', test_check_args, env : test_env, suite : 'base')
endif

# exit test
test_exit = executable('test_exit',
    'test_exit.c',
    include_directories : chl_inc,
    link_with : chlib,
    name_suffix : exe_name_suffix)
test('chl/exit', test_exit, env : test_env, suite : 'base')

constants = executable('constants',
    'constants.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/const', constants, env: test_env, suite: 'base')

# string tests
test_string = executable('test_string',
    'test_string.c',
    include_directories : [chl_inc],
    link_with : [chlib])
test('chl/string', test_string, env: test_env, suite: 'base')

# error tests
test_error = executable('test_error',
    'test_error.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/error', test_error, env: test_env, suite: 'base', )

# xs rect tests
test_xs_rect = executable('test_xs_rect',
    'test_xs_rect.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/rect', test_xs_rect, env: test_env, suite: 'xs')

# xs array
test_xs_array = executable('test_xs_array',
    'test_xs_array.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/array', test_xs_array, env: test_env, suite: 'xs')

# xs subsection
test_xs_subsect = executable('test_xs_subsect',
    'test_xs_subsect.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/subsect', test_xs_subsect, env: test_env, suite: 'xs')

# xs compound
test_xs_comp = executable('test_xs_comp',
    'test_xs_comp.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/comp', test_xs_comp, env: test_env, suite: 'xs')

# reach tests
test_reach = executable('test_reach',
    'test_reach.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/reach', test_reach, env: test_env, suite: 'reach')
