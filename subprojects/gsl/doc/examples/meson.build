# emscripten build
if target_machine.cpu() == 'wasm32'
    exe_name_suffix = 'js'
else
    exe_name_suffix = []
endif


executable('rootnewt',
    ['rootnewt.c'],
    include_directories : inc,
    dependencies : gsl_dep,
    name_suffix : exe_name_suffix)
