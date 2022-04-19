project('gsl', 'c', version : '2.7')

inc = include_directories('include')
gsl_inc = include_directories('.')

subdir('err')
subdir('sys')
subdir('roots')

gsl = static_library('gsl',
    link_whole: [gslroots])

gsl_dep = declare_dependency(include_directories : inc,
  link_with : gsl)

if get_option('build_examples')
  subdir('doc')
endif
