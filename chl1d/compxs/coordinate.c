#include <assert.h>

#include "coordinate.h"
#include "memory.h"

/* Creates and allocate space for a new Coordinate */
Coordinate
coord_new (real y, real z)
{
  Coordinate c;
  NEW (c);

  c->y = y;
  c->z = z;

  return c;
}

/* Makes a copy and returns a new Coordinate */
Coordinate
coord_copy (Coordinate c)
{
  assert (c);
  return coord_new ((c->y), (c->z));
}

/* Frees space from a previously allocated Coordinate */
void
coord_free (Coordinate c)
{
  if (c)
    FREE (c);
}

/* Returns 0 if c1 and c2 are equal */
int
coord_eq (Coordinate c1, Coordinate c2)
{
  if (c1 == c2)
    return 0;
  /* either coordinate is NULL */
  if (!c1 || !c2)
    return 1;

  if (c1->y == c2->y && c1->z == c2->z)
    return 0;
  else
    return 1;
}

/* Linearly interpolates Coordinate z value given a y value */
Coordinate
coord_interp_z (Coordinate c1, Coordinate c2, real y)
{
  assert (c1 && c2);

  /* assert y is between the two points */
  assert ((c1->y <= y && y <= c2->y) || (c2->y <= y && y <= c1->y));

  real slope = (c2->z - c1->z) / (c2->y - c1->y);
  real z     = slope * (y - c1->y) + c1->z;
  return coord_new (y, z);
}

/* Linearly interpolates Coordinate z value given a y value */
Coordinate
coord_interp_y (Coordinate c1, Coordinate c2, real z)
{
  assert (c1 && c2);

  /* assert z is between the two points */
  assert ((c1->z <= z && z <= c2->z) || (c2->z <= z && z <= c1->z));

  real slope = (c2->y - c1->y) / (c2->z - c1->z);
  real y     = slope * (z - c1->z) + c1->y;
  return coord_new (y, z);
}
