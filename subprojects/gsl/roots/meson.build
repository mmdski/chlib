gsl_roots_sources = [
  'convergence.c',
  'fdfsolver.c',
  'newton.c'
]

gslroots = static_library('gslroots',
    gsl_roots_sources,
    include_directories: [inc, gsl_inc],
    link_with: [gslerr, gslsys])
