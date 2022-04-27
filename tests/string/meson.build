test_new = executable('test_new',
    'new.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])
test_free = executable('test_free',
    'free.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])
test_get = executable('test_get',
    'get.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])
test_copy = executable('test_copy',
    'copy.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])
test_eq = executable('test_eq',
    'eq.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])

test('chl/string/new', test_new, env: test_env, suite: 'string')
test('chl/string/free', test_free, env: test_env, suite: 'string')
test('chl/string/get', test_get, env: test_env, suite: 'string')
test('chl/string/copy', test_copy, env: test_env, suite: 'string')
test('chl/string/eq', test_copy, env: test_env, suite: 'string')
