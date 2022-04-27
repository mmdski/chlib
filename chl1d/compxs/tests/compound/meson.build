test_new = executable('test_new',
    'new.c',
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs])
test_free = executable('test_free',
    'free.c',
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs])
test_props = executable('test_props',
    ['props.c', 'rectangle.c', 'comprect.c'],
    include_directories : [chl_inc, chl1dcompxs_inc, test_inc],
    link_with : [chl1dcompxs])

test('chl/1d/compxs/new', test_new, env: test_env, suite: 'chl1d')
test('chl/1d/compxs/free', test_free, env: test_env, suite: 'chl1d')
test('chl/1d/compxs/props', test_props, env: test_env, suite: 'chl1d')
