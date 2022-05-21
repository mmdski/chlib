# gnuplot is required for visualization
find_program(GNUPLOT_PATH NAMES gnuplot)

add_chlib_exe(string)
add_chlib_exe(error)
add_chlib_exe(errorstack)

add_subdirectory(xs_rect)
