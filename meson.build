project('chlib', 'c',
    default_options : [
        'c_std=c99',
        'c_args=-Wall',
        'b_ndebug=if-release'],
    version : '0.0.0')

if get_option('check_args')
    add_project_arguments('-DCHECK_ARGS', language : 'c')
endif

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required : false)

# emscripten build
if target_machine.cpu() == 'wasm32'
    js_install_dir = 'js'
    exe_name_suffix = 'js'
else
    exe_name_suffix = []
endif

chl_inc = include_directories('include')
subdir('src')

if get_option('tests')

    # test environment
    test_env = environment()
    test_inc = include_directories('tests')

    # run memory tests if ASAN is enabled
    if get_option('b_sanitize') == 'address'
        test_env.set('ASAN_OPTIONS', 'detect_leaks=1')

        # add leak suppression if on macOS
        if build_machine.system() == 'darwin'
            lsan_supp = meson.current_source_dir() + '/lsan.supp'
            test_env.set('LSAN_OPTIONS', 'suppressions=' + lsan_supp)
        endif
    endif

    subdir('tests')
endif


# util_inc = include_directories('chlutil')
# subdir('chlutil')

# subdir('chl1d')

# chlib = static_library('chlib',
    # link_whole : [chlutil, chl1d])

# if get_option('build_app')
    # subdir('app')
# endif
