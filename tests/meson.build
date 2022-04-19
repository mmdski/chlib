test_env = environment()

test_inc = include_directories('.')

# run memory tests if ASAN is enabled
if get_option('b_sanitize') == 'address'
  test_env.set('ASAN_OPTIONS', 'detect_leaks=1')

  # add leak suppression if on macOS
  if build_machine.system() == 'darwin'
    lsan_supp = meson.current_source_dir() + '/lsan.supp'
    test_env.set('LSAN_OPTIONS', 'suppressions=' + lsan_supp)
  endif

  subdir('memory')

endif

subdir('constants')
subdir('error')
subdir('string')
subdir('xsection')
