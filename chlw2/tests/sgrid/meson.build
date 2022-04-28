test_new = executable('test_new',
    'new.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlw2])
test_free = executable('test_free',
    'free.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlw2])
test_setget = executable('test_setget',
    'setget.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlw2])

test('chl/w2/sgrid/new', test_new, env: test_env, suite: 'chlw2')
test('chl/w2/sgrid/free', test_free, env: test_env, suite: 'chlw2')
test('chl/w2/sgrid/setget', test_setget, env: test_env, suite: 'chlw2')
