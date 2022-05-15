# run memory tests if ASAN is enabled
if get_option('b_sanitize') == 'address'
  subdir('memory')
endif

# exit test
test_exit = executable('test_exit',
    'test_exit.c',
    include_directories : chl_inc,
    link_with : chlib,
    name_suffix : exe_name_suffix)
test('test_exit', test_exit, env : test_env, suite : 'base')

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
xs_rect_new = executable('xs_rect_new',
    'xs_rect_new.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/rect/new', xs_rect_new, env: test_env, suite: 'xs')

xs_rect_free = executable('xs_rect_free',
    'xs_rect_free.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/rect/free', xs_rect_free, env: test_env, suite: 'xs')


# xs array
xs_array_new = executable('xs_array_new',
    'xs_array_new.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/array/new', xs_array_new, env: test_env, suite: 'xs')

xs_array_free = executable('xs_array_free',
    'xs_array_free.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/array/free', xs_array_free, env: test_env, suite: 'xs')

xs_array_eq = executable('xs_array_eq',
    'xs_array_eq.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/array/eq', xs_array_eq, env: test_env, suite: 'xs')

xs_array_copy = executable('xs_array_copy',
    'xs_array_copy.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/array/copy', xs_array_copy, env: test_env, suite: 'xs')

xs_array_subarray = executable('xs_array_subarray',
    'xs_array_subarray.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/array/subarray', xs_array_subarray, env: test_env, suite: 'xs')

xs_array_vals = executable('xs_array_vals',
    'xs_array_vals.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/array/vals', xs_array_vals, env: test_env, suite: 'xs')


# xs subsection
xs_subsect_new = executable('xs_subsect_new',
    'xs_subsect_new.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/subsect/new', xs_subsect_new, env: test_env, suite: 'xs')

xs_subsect_free = executable('xs_subsect_free',
    'xs_subsect_free.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/subsect/free', xs_subsect_free, env: test_env, suite: 'xs')

xs_subsect_props = executable('xs_subsect_props',
    'xs_subsect_props.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    dependencies : m_dep,
    name_suffix : exe_name_suffix)
test('chl/xs/subsect/props', xs_subsect_props, env: test_env, suite: 'xs')

xs_subsect_rough = executable('xs_subsect_rough',
    'xs_subsect_rough.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/subsect/rough', xs_subsect_rough, env: test_env, suite: 'xs')


# xs compound
xs_comp_new = executable('xs_comp_new',
    'xs_comp_new.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/comp/new', xs_comp_new, env: test_env, suite: 'xs')

xs_comp_free = executable('xs_comp_free',
    'xs_comp_free.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/xs/comp/free', xs_comp_free, env: test_env, suite: 'xs')

xs_comp_props = executable('xs_comp_props',
    'xs_comp_props.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    dependencies: m_dep,
    name_suffix : exe_name_suffix)
test('chl/xs/comp/props', xs_comp_props, env: test_env, suite: 'xs')


# reach tests
reach_new = executable('reach_new',
    'reach_new.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/reach/new', reach_new, env: test_env, suite: 'reach')

reach_free = executable('reach_free',
    'reach_free.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/reach/free', reach_free, env: test_env, suite: 'reach')

reach_set_sta = executable('reach_set_sta',
    'reach_set_sta.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/reach/set/sta', reach_set_sta, env: test_env, suite: 'reach')

reach_get_sta = executable('reach_get_sta',
    'reach_get_sta.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/reach/get/sta', reach_get_sta, env: test_env, suite: 'reach')

reach_get_xsp = executable('reach_get_xsp',
    'reach_get_xsp.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/reach/get/xsp', reach_get_xsp, env: test_env, suite: 'reach')

reach_thalweg = executable('reach_thalweg',
    'reach_thalweg.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/reach/thalweg', reach_thalweg, env: test_env, suite: 'reach')
