test_const = executable('test_const',
    'test.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])

if target_machine.cpu() == 'wasm32'
    test('chl/const', nodejs, args: test_const.full_path(), suite: 'const')
else
    test('chl/const', test_const, env: test_env, suite: 'const')
endif
