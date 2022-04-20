project('chlib', 'c',
    default_options : [
        'c_std=c99',
        'c_args=-Wall',
        'b_ndebug=if-release'],
    version : '0.0.0')

if get_option('real_is_float')
    add_project_arguments('-DREAL_IS_FLOAT', language : 'c')
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

if get_option('gsl_build_examples')
    gsl_proj = subproject('gsl',
        default_options : 'build_examples=true',
        required : true)
else
    gsl_proj = subproject('gsl',
        default_options : 'build_examples=false',
        required : true)
endif
gsl_dep = gsl_proj.get_variable('gsl_dep')

inc = include_directories('include')

subdir('src')

if get_option('build_app')
    subdir('app')
endif

if get_option('build_tests')
    subdir('tests')
endif
