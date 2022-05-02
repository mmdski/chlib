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
test_roughness = executable('test_roughness',
    'roughness.c',
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs],
    name_suffix : exe_name_suffix)
test_props = executable('test_props',
    'props.c',
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs],
    name_suffix : exe_name_suffix)

test('chl/1d/compxs/subsect/new', test_new, env: test_env, suite: 'chl1d')
test('chl/1d/compxs/subsect/free', test_free, env: test_env, suite: 'chl1d')
test('chl/1d/compxs/subsect/roughness', test_roughness, env: test_env, suite: 'chl1d')
test('chl/1d/compxs/subsect/props', test_props, env: test_env, suite: 'chl1d')
