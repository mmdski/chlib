test_new = executable('test_new',
    'new.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])
test_free = executable('test_free',
    'free.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])
test_get = executable('test_get',
    'get.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])
test_copy = executable('test_copy',
    'copy.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])
test_eq = executable('test_eq',
    'eq.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])

test('chl/util/string/new', test_new, env: test_env, suite: 'util')
test('chl/util/string/free', test_free, env: test_env, suite: 'util')
test('chl/util/string/get', test_get, env: test_env, suite: 'util')
test('chl/util/string/copy', test_copy, env: test_env, suite: 'util')
test('chl/util/string/eq', test_copy, env: test_env, suite: 'util')
