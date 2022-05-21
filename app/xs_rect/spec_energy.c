#include <stdio.h>
#include <stdlib.h>

#include <chl/chl_xs.h>

void
compute_spec_energy (
    ChlXSRect xs, double q, size_t n, double *y, double *spec_energy)
{
  for (size_t i = 0; i < n; i++)
    {
      spec_energy[i] = chl_xs_rect_spec_energy (xs, y[i], q, &(spec_energy[i]));
    }
}

int
main (void)
{
  FILE *gnuplot;
  if ((gnuplot = popen ("gnuplot -persistent", "w")) == NULL)
    {
      fputs ("Unable to open pipe to gnuplot\n", stderr);
      return EXIT_FAILURE;
    }

  fputs ("set title \"Specific energy\" font \",20\"\n", gnuplot);
  fputs ("set key left top box font \",20\"\n", gnuplot);
  fputs ("set xlabel \"Specific energy, in m\" font \",15\"\n", gnuplot);
  fputs ("set ylabel \"Depth, in m\" font \",15\"\n", gnuplot);
  fputs ("plot '-' notitle \"Specific Energy\" with lines\n", gnuplot);

  size_t n     = 100;
  double q     = 10;
  double y_min = 0.1;
  double y_max = 5;
  double dy    = (y_max - y_min) / n;
  double spec_energy;
  double y;
  double width = 10;

  ChlXSRect xs;
  if ((xs = chl_xs_rect_new (width)) == NULL)
    goto fail;

  for (size_t i = 0; i < n; i++)
    {
      y = y_min + i * dy;
      if (chl_xs_rect_spec_energy (xs, y, q, &spec_energy) < 0)
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
