# tests to verify ASAN and LSAN are working properly

no_leak = executable('no-leak',
    'no-leak.c')
memory_leak = executable('memory-leak',
    'memory-leak.c')
double_free = executable('double-free',
    'double-free.c')
access_after_free = executable('access-after-free',
    'access-after-free.c')

test('no-leak', no_leak, env: test_env, should_fail: false, suite: 'memory')
test('memory-leak', memory_leak, env: test_env, should_fail: true, suite: 'memory')
test('access-after-free', access_after_free, env: test_env, should_fail: true, suite: 'memory')
test('testdoublefree', double_free, env: test_env, should_fail: true, suite: 'memory')
