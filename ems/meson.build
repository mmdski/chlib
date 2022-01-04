chl_ems_sources = ['matrix.c', chl_sources]

js_name = meson.project_name()

executable(js_name,
    chl_ems_sources,
    include_directories: inc,
    c_args: chlib_c_args,
    name_suffix: 'js',
    install: true,
    install_dir: js_install_dir)
