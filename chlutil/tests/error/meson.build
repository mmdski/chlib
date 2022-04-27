test_new = executable('test_new',
    'new.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])
test_free = executable('test_free',
    'free.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])
test_istype = executable('test_istype',
    'istype.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])
test_raise = executable('test_raise',
    'raise.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])
test_raise_fail = executable('test_raise_fail',
    'raisefail.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])
test_stack_check = executable('test_stack_check',
    'stackcheck.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])
test_stack_check_fail = executable('test_stack_check_fail',
    'stackcheckfail.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])


test('chl/util/err/new', test_new, env: test_env, suite: 'util')
test('chl/util/err/free', test_free, env: test_env, suite: 'util')
test('chl/util/err/istype', test_istype, env: test_env, suite: 'util')
test('chl/util/err/raise', test_raise, env: test_env, suite: 'util')
test('chl/util/err/raise fail', test_raise_fail, env: test_env, should_fail: true, suite: 'util')
test('chl/util/err/stack check', test_stack_check, env: test_env, suite: 'util')
test('chl/util/err/stack check fail', test_stack_check_fail, env: test_env, should_fail: true, suite: 'util')
