test_new = executable('test_new',
    'new.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])
test_free = executable('test_free',
    'free.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])
test_istype = executable('test_istype',
    'istype.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])
test_raise = executable('test_raise',
    'raise.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])
test_raise_fail = executable('test_raise_fail',
    'raisefail.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])
test_stack_check = executable('test_stack_check',
    'stackcheck.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])
test_stack_check_fail = executable('test_stack_check_fail',
    'stackcheckfail.c',
    include_directories : [chl_inc, test_inc],
    link_with : [chlib])


test('chl/err/new', test_new, env: test_env, suite: 'err')
test('chl/err/free', test_free, env: test_env, suite: 'err')
test('chl/err/istype', test_istype, env: test_env, suite: 'err')
test('chl/err/raise', test_raise, env: test_env, suite: 'err')
test('chl/err/raise fail', test_raise_fail, env: test_env, should_fail: true, suite: 'err')
test('chl/err/stack check', test_stack_check, env: test_env, suite: 'err')
test('chl/err/stack check fail', test_stack_check_fail, env: test_env, should_fail: true, suite: 'err')
