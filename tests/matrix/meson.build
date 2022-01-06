test_new = executable('test_new',
    'new.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_new_from = executable('test_new_from',
    'new_from.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_zeros = executable('test_zeros',
    'zeros.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_eye = executable('test_eye',
    'eye.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_eq = executable('test_eq',
    'eq.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_size = executable('test_size',
    'size.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_mult = executable('test_mult',
    'mult.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_transpose = executable('test_transpose',
    'mult.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])

test('chl/matrix/new', test_new, env: test_env, suite: 'matrix')
test('chl/matrix/new_from', test_new_from, env: test_env, suite: 'matrix')
test('chl/matrix/zeros', test_zeros, env: test_env, suite: 'matrix')
test('chl/matrix/eye', test_eye, env: test_env, suite: 'matrix')
test('chl/matrix/eq', test_eq, env: test_env, suite: 'matrix')
test('chl/matrix/size', test_size, env: test_env, suite: 'matrix')
test('chl/matrix/multiply', test_mult, env: test_env, suite: 'matrix')
test('chl/matrix/transpose', test_transpose, env: test_env, suite: 'matrix')
