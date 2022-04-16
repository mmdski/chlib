gsl_inc = include_directories('.')

subdir('err')
subdir('sys')
subdir('roots')

gsl = static_library('gsl',
    include_directories: inc,
    link_with: [gslroots])
