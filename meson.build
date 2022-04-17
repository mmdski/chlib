project('chlib', 'c',
    default_options : [
        'c_std=c99',
        'c_args=-Wall',
        'b_ndebug=if-release'],
    version : '0.0.0')

if get_option('real_is_float')
    add_project_arguments('-DREAL_IS_FLOAT', language : 'c')
endif

# emscripten build
if target_machine.cpu() == 'wasm32'
    js_install_dir = 'js'
    exe_name_suffix = 'js'
else
    exe_name_suffix = []
endif

inc = include_directories('include')

subdir('gsl')

subdir('src')

if get_option('build_app')
    subdir('app')
endif

if get_option('build_tests')
    subdir('tests')
endif
