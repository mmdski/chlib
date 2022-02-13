test_new = executable('test_new',
    'new.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_free = executable('test_free',
    'free.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_istype = executable('test_istype',
    'istype.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])

test('chl/err/new', test_new, env: test_env, suite: 'err')
test('chl/err/free', test_free, env: test_env, suite: 'err')
test('chl/err/istype', test_istype, env: test_env, suite: 'err')
