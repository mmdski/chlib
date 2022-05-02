test_new = executable('test_new',
    'new.c',
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs],
    name_suffix : exe_name_suffix)
test_free = executable('test_free',
    'free.c',
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs],
    name_suffix : exe_name_suffix)
test_eq = executable('test_eq',
    'eq.c',
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs],
    name_suffix : exe_name_suffix)
test_copy = executable('test_copy',
    'copy.c',
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs],
    name_suffix : exe_name_suffix)
test_vals = executable('test_vals',
    'vals.c',
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs],
    name_suffix : exe_name_suffix)
test_subarray = executable('test_subarray',
    'subarray.c',
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs],
    name_suffix : exe_name_suffix)

test('chl/1d/compxs/array/new', test_new, env: test_env, suite: 'chl1d')
test('chl/1d/compxs/array/free', test_free, env: test_env, suite: 'chl1d')
test('chl/1d/compxs/array/eq', test_eq, env: test_env, suite: 'chl1d')
test('chl/1d/compxs/array/copy', test_copy, env: test_env, suite: 'chl1d')
test('chl/1d/compxs/array/vals', test_vals, env: test_env, suite: 'chl1d')
test('chl/1d/compxs/array/subarray', test_subarray, env: test_env, suite: 'chl1d')
