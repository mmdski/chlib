test_env = environment()
test_env.set('ASAN_OPTIONS', 'detect_leaks=1')

matrix_mem_test = executable('matrix_mem_test',
    'matrix_mem_test.c',
    include_directories: [inc],
    link_with: [chlib])

test('matrix_mem_test',
    matrix_mem_test,
    env: test_env,
    suite: 'memory')
