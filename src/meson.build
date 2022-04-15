chl_sources = files(
    [
        'error.c',
        'memory.c',
        'string.c',
        'xsection.c'
    ]
)
chlib_c_args = ['-DCHL_COMPILATION']

if target_machine.cpu() != 'wasm32'
    chlib = static_library('chlib',
        chl_sources,
        include_directories: inc,
        c_args: chlib_c_args)
endif
