test_new = executable('test_new',
    'new.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_free = executable('test_free',
    'free.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])

test('chl/xs/compound/new', test_new, env: test_env, suite: 'xs')
test('chl/xs/compound/free', test_free, env: test_env, suite: 'xs')
