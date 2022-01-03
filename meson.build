project('chlib', 'c',
    default_options : ['c_std=c99', 'c_args=-Wall', 'b_ndebug=if-release'],
    version : '0.0.0')

js_install_dir = meson.source_root() / 'assets' / 'js'

if get_option('real_is_float')
    add_project_arguments('-DREAL_IS_FLOAT', language : 'c')
endif

inc = include_directories('include')

subdir('src')

if target_machine.cpu() == 'x86_64'
    subdir('app')
    subdir('tests')
endif

# emscripten build
if target_machine.cpu() == 'wasm32'
    subdir('ems')
endif
