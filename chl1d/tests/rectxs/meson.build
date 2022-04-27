test_new = executable('test_new',
    'new.c',
    include_directories : [chl_inc, chl1d_inc, test_inc],
    link_with : [chl1d])
test_free = executable('test_free',
    'free.c',
    include_directories : [chl_inc, chl1d_inc, test_inc],
    link_with : [chl1d])

test('chl/1d/rectxs/new', test_new, env: test_env, suite: 'chl1d')
test('chl/1d/rectxs/free', test_free, env: test_env, suite: 'chl1d')
