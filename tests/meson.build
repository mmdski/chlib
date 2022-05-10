# run memory tests if ASAN is enabled
if get_option('b_sanitize') == 'address'
  subdir('memory')
endif

constants = executable('constants',
    'constants.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/const', constants, env: test_env, suite: 'base')


# string tests
string_new = executable('string_new',
    'string_new.c',
    include_directories : [chl_inc],
    link_with : [chlib])
test('chl/string/new', string_new, env: test_env, suite: 'base')

string_free = executable('string_free',
    'string_free.c',
    include_directories : [chl_inc],
    link_with : [chlib])
test('chl/string/free', string_free, env: test_env, suite: 'base')

string_get = executable('string_get',
    'string_get.c',
    include_directories : [chl_inc],
    link_with : [chlib])
test('chl/string/get', string_get, env: test_env, suite: 'base')

string_copy = executable('string_copy',
    'string_copy.c',
    include_directories : [chl_inc],
    link_with : [chlib])
test('chl/string/copy', string_copy, env: test_env, suite: 'base')

string_eq = executable('string_eq',
    'string_eq.c',
    include_directories : [chl_inc],
    link_with : [chlib])
test('chl/string/eq', string_copy, env: test_env, suite: 'base')


# error tests
error_new = executable('error_new',
    'error_new.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/err/new', error_new, env: test_env, suite: 'base')

error_free = executable('error_free',
    'error_free.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/err/free', error_free, env: test_env, suite: 'base')

error_istype = executable('error_istype',
    'error_istype.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/err/istype', error_istype, env: test_env, suite: 'base')

error_raise = executable('error_raise',
    'error_raise.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/err/raise', error_raise, env: test_env, suite: 'base')

error_raise_fail = executable('error_raise_fail',
    'error_raise_fail.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/err/raise_fail', error_raise_fail, env: test_env, should_fail: true, suite: 'base', )

error_stack_check = executable('error_stack_check',
    'error_stack_check.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/err/stack_check', error_stack_check, env: test_env, suite: 'base')

error_stack_check_fail = executable('error_stack_check_fail',
    'error_stack_check_fail.c',
    include_directories : [chl_inc],
    link_with : [chlib],
    name_suffix : exe_name_suffix)
test('chl/err/stack_check_fail', error_stack_check_fail, env: test_env, should_fail: true, suite: 'base', )


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
    name_suffix : exe_name_suffix)
test('chl/xs/comp/props', xs_comp_props, env: test_env, suite: 'xs')
