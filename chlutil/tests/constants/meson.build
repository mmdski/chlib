test_const = executable('test_const',
    'test.c',
    include_directories : [chl_inc, util_inc, test_inc],
    link_with : [chlutil])

test('chl/const', test_const, env: test_env, suite: 'util')
