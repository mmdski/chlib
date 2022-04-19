test_new = executable('test_new',
    'new.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_free = executable('test_free',
    'free.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_roughness = executable('test_roughness',
    'roughness.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_area = executable('test_area',
    'area.c',
    include_directories : [inc, test_inc],
    link_with : [chlib, xs_test_lib])


if target_machine.cpu() == 'wasm32'
    test('chl/xs/subsect/new', nodejs, args: test_new.full_path(), suite: 'xs')
    test('chl/xs/subsect/free', nodejs, args: test_free.full_path(), suite: 'xs')
    test('chl/xs/subsect/roughness', nodejs, args: test_roughness.full_path(), suite: 'xs')
    test('chl/xs/subsect/area', nodejs, args: test_area.full_path(), suite: 'xs')
else
    test('chl/xs/subsect/new', test_new, env: test_env, suite: 'xs')
    test('chl/xs/subsect/free', test_free, env: test_env, suite: 'xs')
    test('chl/xs/subsect/roughness', test_roughness, env: test_env, suite: 'xs')
    test('chl/xs/subsect/area', test_area, env: test_env, suite: 'xs')
endif
