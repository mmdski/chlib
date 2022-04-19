test_new = executable('test_new',
    'new.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_free = executable('test_free',
    'free.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])

if target_machine.cpu() == 'wasm32'
    test('chl/xs_rect/new', nodejs, args: test_new.full_path(), suite: 'xs')
    test('chl/xs_rect/free', nodejs, args: test_free.full_path(), suite: 'xs')
else
    test('chl/xs_rect/new', test_new, env: test_env, suite: 'xs')
    test('chl/xs_rect/free', test_free, env: test_env, suite: 'xs')
endif
