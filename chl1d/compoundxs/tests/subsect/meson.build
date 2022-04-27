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
test_props = executable('test_props',
    'props.c',
    include_directories : [inc, test_inc],
    link_with : [chlib])

test('chl/xs/subsect/new', test_new, env: test_env, suite: 'xs')
test('chl/xs/subsect/free', test_free, env: test_env, suite: 'xs')
test('chl/xs/subsect/roughness', test_roughness, env: test_env, suite: 'xs')
test('chl/xs/subsect/props', test_props, env: test_env, suite: 'xs')
