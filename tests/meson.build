test_env = environment()
test_env.set('ASAN_OPTIONS', 'detect_leaks=1')

# add leak suppression if on macOS
if build_machine.system() == 'darwin'
  lsan_supp = meson.current_source_dir() + '/lsan.supp'
  test_env.set('LSAN_OPTIONS', 'suppressions=' + lsan_supp)
endif

test_inc = include_directories('.')

subdir('error')
subdir('string')
subdir('xs')
