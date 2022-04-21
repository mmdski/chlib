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
    link_with : [chlib])
test_wp = executable('test_wp',
    'wp.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_tw = executable('test_tw',
    'tw.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])
test_hr = executable('test_hr',
    'hr.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])


if target_machine.cpu() == 'wasm32'
    test('chl/xs/subsect/new', nodejs, args: test_new.full_path(), suite: 'xs')
    test('chl/xs/subsect/free', nodejs, args: test_free.full_path(), suite: 'xs')
    test('chl/xs/subsect/roughness', nodejs, args: test_roughness.full_path(), suite: 'xs')
    test('chl/xs/subsect/area', nodejs, args: test_area.full_path(), suite: 'xs')
    test('chl/xs/subsect/wp', nodejs, args: test_wp.full_path(), suite: 'xs')
    test('chl/xs/subsect/tw', nodejs, args: test_tw.full_path(), suite: 'xs')
    test('chl/xs/subsect/hr', nodejs, args: test_hr.full_path(), suite: 'xs')
else
    test('chl/xs/subsect/new', test_new, env: test_env, suite: 'xs')
    test('chl/xs/subsect/free', test_free, env: test_env, suite: 'xs')
    test('chl/xs/subsect/roughness', test_roughness, env: test_env, suite: 'xs')
    test('chl/xs/subsect/area', test_area, env: test_env, suite: 'xs')
    test('chl/xs/subsect/wp', test_wp, env: test_env, suite: 'xs')
    test('chl/xs/subsect/tw', test_tw, env: test_env, suite: 'xs')
    test('chl/xs/subsect/hr', test_hr, env: test_env, suite: 'xs')
endif
