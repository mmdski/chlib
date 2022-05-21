#include <stdio.h>
#include <stdlib.h>

#include <chl/chl_io.h>
#include <chl/chl_xs.h>

int
main (void)
{
  FILE *gnuplot;
  if ((gnuplot = chl_popen ("gnuplot -persistent", "w")) == NULL)
    {
      fputs ("Unable to open pipe to gnuplot\n", stderr);
      return EXIT_FAILURE;
    }

  fputs ("set title \"Specific energy\" font \",20\"\n", gnuplot);
  fputs ("set key left top box font \",20\"\n", gnuplot);
  fputs ("set xlabel \"Specific energy, in m\" font \",15\"\n", gnuplot);
  fputs ("set ylabel \"Depth, in m\" font \",15\"\n", gnuplot);

  size_t n     = 100;
  double q1    = 1;
  double q2    = 5;
  double q3    = 10;
  double y_min = 0.001;
  double y_max = 1;
  double dy    = (y_max - y_min) / (n - 1);
  double spec_energy;
  double y;
  double width = 25;

  fprintf (gnuplot, "set xrange [ 0 : %g ] noreverse writeback\n", y_max);
  fprintf (gnuplot, "set yrange [ 0 : %g ] noreverse writeback\n", y_max);

  fprintf (gnuplot,
           "plot "
           "'-' title \"Q = %g cms\" with lines,"   // q1
           "'-' title \"Q = %g cms\" with lines,"   // q2
           "'-' title \"Q = %g cms\" with lines\n", // q3
           q1,
           q2,
           q3);

  ChlXSRect xs;
  if ((xs = chl_xs_rect_new (width)) == NULL)
    goto fail;

  // plot specific energy for q1
  for (size_t i = 0; i < n; i++)
    {
      y = y_min + i * dy;
      if (chl_xs_rect_spec_energy (xs, y, q1, &spec_energy) < 0)
        goto fail;
      fprintf (gnuplot, "%g %g\n", spec_energy, y);
    }
  fputs ("e\n", gnuplot);

  // plot specific energy for q2
  for (size_t i = 0; i < n; i++)
    {
      y = y_min + i * dy;
      if (chl_xs_rect_spec_energy (xs, y, q2, &spec_energy) < 0)
        goto fail;
      fprintf (gnuplot, "%g %g\n", spec_energy, y);
    }
  fputs ("e\n", gnuplot);

  // plot specific energy for q3
  for (size_t i = 0; i < n; i++)
    {
      y = y_min + i * dy;
      if (chl_xs_rect_spec_energy (xs, y, q3, &spec_energy) < 0)
        goto fail;
      fprintf (gnuplot, "%g %g\n", spec_energy, y);
    }
  fputs ("e\n", gnuplot);

  fflush (gnuplot);
  chl_xs_rect_free (xs);
  return EXIT_SUCCESS;

fail:
  fputs ("spec_energy.c failed\n", stderr);
  chl_xs_rect_free (xs);
  fflush (gnuplot);
  return EXIT_FAILURE;
}
