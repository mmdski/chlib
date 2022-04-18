test_new = executable('test_new',
    'new.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_free = executable('test_free',
    'free.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_eq = executable('test_eq',
    'eq.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_copy = executable('test_copy',
    'copy.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])

test('chl/xs/array/new', test_new, env: test_env, suite: 'xs')
test('chl/xs/array/free', test_new, env: test_env, suite: 'xs')
test('chl/xs/array/eq', test_new, env: test_env, suite: 'xs')
test('chl/xs/array/copy', test_copy, env: test_env, suite: 'xs')
