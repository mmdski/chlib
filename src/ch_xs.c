#include <stdlib.h>

#include <chl/xs.h>

ChXSDefinition *
ch_xs_def_new (void)
{

  ChXSDefinition *xs_def = malloc (sizeof (ChXSDefinition));
  return xs_def;
}

void
ch_xs_def_free (ChXSDefinition *xs_def)
{
  if (!xs_def)
    return;

  free (xs_def);
}
