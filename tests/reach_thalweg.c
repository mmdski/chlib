#include <stdlib.h>

#include <chl/chl_error.h>
#include <chl/chl_reach.h>

#include "chlassert.h"

int
main (void)
{
  size_t n_nodes = 10;

  ChlReach reach = chl_reach_new (n_nodes);

  double reach_length = 100;
  double bed_slope    = 0.001;
  double bed_height   = reach_length * bed_slope;

  double dx     = reach_length / (double) n_nodes;
  double dy     = bed_height / (double) n_nodes;
  double x_dist = 0;

  double *thalweg_check = calloc (reach->n_nodes, sizeof (double));

  for (size_t i = 0; i < n_nodes; i++)
    {
      if (chl_reach_set_sta (reach, i, NULL, NULL, bed_height, x_dist) < 0)
        {
          chl_err_stack_print (__FILE__, __LINE__);
          return EXIT_FAILURE;
        }
      thalweg_check[i] = bed_height;
      x_dist += dx;
      bed_height -= dy;
    }

  double *thalweg = calloc ((reach->n_nodes), sizeof (double));
  if (chl_reach_thalweg (reach, &thalweg) < 0)
    {
      chl_err_stack_print (__FILE__, __LINE__);
      return EXIT_FAILURE;
    }

  for (size_t i = 0; i < n_nodes; i++)
    {
      assert_equal (thalweg_check[i], thalweg[i]);
    }

  chl_reach_free (reach);
  free (thalweg_check);
  free (thalweg);

  chl_err_stack_check (__FILE__, __LINE__);
  return EXIT_SUCCESS;
}
