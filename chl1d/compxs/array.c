#include <assert.h>
#include <math.h>
#include <stddef.h>

#include <chl/chl1d.h>
#include <chl/chlerror.h>

#include "array.h"
#include "coordinate.h"
#include "error.h"
#include "list.h"
#include "memory.h"

struct ChlXSArray
{
  int         length;      /* number of coordinates in this array */
  double      max_y;       /* maximum y in chl_xs_array */
  double      min_y;       /* minimum y in chl_xs_array */
  Coordinate *coordinates; /* array of coordinates */
};

static int
check_z_coordinates (int n, Coordinate *coordinates)
{
  assert (coordinates);

  for (int i = 1; i < n; i++)
    {
      if ((*(coordinates + i - 1))->z > (*(coordinates + i))->z)
        return -1;
    }

  return 0;
}

ChlXSArray
chl_xs_array_new (int n, double *y, double *z)
{
  if (y == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "y-array is NULL", __FILE__, __LINE__);
      return NULL;
    }
  if (z == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "z-array is NULL", __FILE__, __LINE__);
      return NULL;
    }

  double     max_y = -INFINITY;
  double     min_y = INFINITY;
  ChlXSArray a;
  NEW (a);

  a->length      = n;
  a->coordinates = chl_calloc (n, sizeof (Coordinate));

  int i;
  for (i = 0; i < n; i++)
    {
      *(a->coordinates + i) = coord_new (*(y + i), *(z + i));
      if (*(y + i) > max_y)
        max_y = *(y + i);
      if (*(y + i) < min_y)
        min_y = *(y + i);
    }
  a->max_y = max_y;
  a->min_y = min_y;

  if (check_z_coordinates (n, a->coordinates) < 0)
    {
      chl_err_raise (VALUE_ERROR,
                     "z-coordinates must be in ascending order",
                     __FILE__,
                     __LINE__);
      chl_xs_array_free (a);
      goto fail;
    }

  return a;

fail:
  return NULL;
}

static ChlXSArray
chl_xs_array_from_array (int n, Coordinate *array)
{
  assert (array);

  ChlXSArray  a;
  Coordinate *coordinates;
  double      max_y = -INFINITY;
  double      min_y = INFINITY;

  Coordinate c;

  if (n > 0)
    {
      coordinates = chl_calloc (n, sizeof (Coordinate));
      for (int i = 0; i < n; i++)
        {
          c                  = *(array + i);
          *(coordinates + i) = c;
          if (c)
            {
              if (c->y > max_y)
                max_y = c->y;
              if (c->y < min_y)
                min_y = c->y;
            }
        }
    }
  else
    coordinates = NULL;

  NEW (a);
  a->coordinates = coordinates;
  a->length      = n;
  a->max_y       = max_y;
  a->min_y       = min_y;

  return a;
}

ChlXSArray
chl_xs_array_copy (ChlXSArray ca)
{
  if (ca == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "XS array is NULL", __FILE__, __LINE__);
      return NULL;
    }

  int n = ca->length;

  Coordinate *coordinates = chl_calloc (n, sizeof (Coordinate));
  ChlXSArray  copy;

  for (int i = 0; i < n; i++)
    coordinates[i] = coord_copy (ca->coordinates[i]);

  copy = chl_xs_array_from_array (n, coordinates);
  chl_free (coordinates);

  return copy;
}

void
chl_xs_array_free (ChlXSArray a)
{
  if (!a)
    return;

  int        i;
  Coordinate c;
  for (i = 0; i < a->length; i++)
    {
      c = *(a->coordinates + i);
      coord_free (c);
    }

  chl_free ((void *) a->coordinates);

  FREE (a);
}

bool
chl_xs_array_eq (ChlXSArray a1, ChlXSArray a2)
{

  Coordinate c1;
  Coordinate c2;

  int i;

  /* check for either NULL */
  if ((a1 == NULL) || (a2 == NULL))
    return false;

  if (a1 == a2)
    return true;

  if (a1->length != a2->length)
    return false;

  for (i = 0; i < a1->length; i++)
    {
      c1 = *(a1->coordinates + i);
      c2 = *(a2->coordinates + i);
      if (coord_eq (c1, c2) != 0)
        return false;
    }

  return true;
}

double
chl_xs_array_max_y (ChlXSArray a)
{
  assert (a);
  return a->max_y;
}

double
chl_xs_array_min_y (ChlXSArray a)
{
  assert (a);
  return a->min_y;
}

int
chl_xs_array_length (ChlXSArray a)
{
  if (a == NULL)
    {
      chl_err_raise (
          NULL_ARGUMENT_ERROR, "XS array is NULL", __FILE__, __LINE__);
      return -1;
    }
  return a->length;
}

Coordinate
chl_xs_array_get (ChlXSArray a, int i)
{
  assert (a);
  assert (0 <= i && i < a->length);

  if (a->coordinates[i])
    return coord_copy (a->coordinates[i]);
  else
    return NULL;
}

int
chl_xs_array_vals (ChlXSArray a, double *elevation, double *station)
{
  if (a == NULL)
    RAISE_NULL_ERR_INT;

  int len = a->length;

  Coordinate c;

  for (int i = 0; i < len; i++)
    {
      c                = chl_xs_array_get (a, i);
      *(elevation + i) = c->z;
      *(station + i)   = c->y;
      coord_free (c);
    }

  return len;
}

/* find the index of the coordinate with the greatest z value that's less than
 * or equal to zlo */
static int
find_zlo_idx (ChlXSArray a, int lo, int hi, double zlo)
{
  if (lo == hi)
    {
      while (lo > 0 && a->coordinates[lo - 1]->z >= zlo)
        {
          lo--;
        }
      return a->coordinates[lo]->z <= zlo ? lo : -1;
    }

  int mid = (hi + lo) / 2;

  if (zlo < a->coordinates[mid]->z)
    return find_zlo_idx (a, lo, mid, zlo);

  int ret = find_zlo_idx (a, mid + 1, hi, zlo);

  return ret == -1 ? mid : ret;
}

static int
find_zhi_idx (ChlXSArray a, int n, int lo, int hi, double zhi)
{
  if (lo == hi)
    {
      while (hi < n - 1 && a->coordinates[hi + 1]->z <= zhi)
        {
          hi++;
        }
      // while (hi < n && a->coordinates[hi + 1]->z == a->coordinates[hi]->z &&
      //        a->coordinates[hi + 1]->y >= a->coordinates[hi]->y)
      //   {
      //     hi++;
      //   }
      return a->coordinates[hi]->z >= zhi ? hi : -1;
    }

  int mid = (hi + lo) / 2;

  if (zhi <= a->coordinates[mid]->z)
    return find_zhi_idx (a, n, lo, mid, zhi);

  int ret = find_zhi_idx (a, n, mid + 1, hi, zhi);

  return ret == -1 ? mid : ret;
}

ChlXSArray
chl_xs_array_subarray_y (ChlXSArray a, double y)
{
  assert (a);

  int n = a->length;

  /* subarray to return */
  int         sa_length;
  List        list = list_new ();
  ChlXSArray  sa;
  Coordinate *coordinates;

  /* loop variables */
  Coordinate c1     = NULL;
  Coordinate c2     = NULL;
  Coordinate c_last = NULL; /* keep track of the last coordinate added */

  /* check the first coordinate */
  c1 = *(a->coordinates);

  /* if the y of the coordinate is less than or equal to y, add the
   * coordinate to the list
   */
  if (c1->y <= y)
    {
      c_last = coord_copy (c1);
      list_append (list, c_last);
    }

  for (int i = 1; i < n; i++)
    {

      c1 = *(a->coordinates + i - 1);
      c2 = *(a->coordinates + i);

      /* add an interpolated coordinate if coordinates change from
       * above to below or below to above the y value
       */
      if ((c1->y < y && y < c2->y) || (y < c1->y && c2->y < y))
        {
          c_last = coord_interp_z (c1, c2, y);
          list_append (list, c_last);
        }

      /* add c2 if c2.z is at or below z */
      if (c2->y <= y)
        {
          c_last = coord_copy (c2);
          list_append (list, c_last);
        }

      /* if the last coordinate added wasn't NULL,
       * c2 isn't the last coordinate in the array,
       * and c2 is above y,
       * add a NULL spot in the
       */
      if (c_last != NULL && (i < n - 1) && (c2->y > y))
        {
          c_last = NULL;
          list_append (list, c_last);
        }
    }

  sa_length = list_length (list);

  /* don't include the last coordinate if it was null */
  if (c_last == NULL)
    sa_length--;

  coordinates = (Coordinate *) list_to_array (list);
  list_free (list);
  sa = chl_xs_array_from_array (sa_length, coordinates);
  chl_free (coordinates);

  return sa;
}

static int
find_high_elev (ChlXSArray a, int i)
{
  int len = a->length;
  if (i == 0)
    {
      if (a->coordinates[i + 1]->y > a->coordinates[i]->y &&
          a->coordinates[i + 1]->z == a->coordinates[i]->z)
        return find_high_elev (a, i + 1);
      else
        return i;
    }
  else if (i == (len - 1))
    {
      if (a->coordinates[i - 1]->y > a->coordinates[i]->y &&
          a->coordinates[i - 1]->z == a->coordinates[i]->z)
        return find_high_elev (a, i - 1);
      else
        return i;
    }
  else
    {
      if (a->coordinates[i + 1]->y > a->coordinates[i]->y &&
          a->coordinates[i + 1]->z == a->coordinates[i]->z)
        return find_high_elev (a, i + 1);
      else if (a->coordinates[i - 1]->y > a->coordinates[i]->y &&
               a->coordinates[i - 1]->z == a->coordinates[i]->z)
        return find_high_elev (a, i - 1);
      else
        return i;
    }
}

ChlXSArray
chl_xs_array_subarray (ChlXSArray a, double zlo, double zhi)
{
  if (!a)
    RAISE_NULL_ERR_NULL;

  if (zhi <= zlo)
    {
      chl_err_raise (INVALID_ARGUMENT_ERROR,
                     "sta_hi must be > sta_lo",
                     __FILE__,
                     __LINE__);
      return NULL;
    }

  if (a->coordinates[0]->z > zlo)
    {
      chl_err_raise (INVALID_ARGUMENT_ERROR,
                     "sta_lo must be greater than or equal to first station",
                     __FILE__,
                     __LINE__);
      return NULL;
    }

  if (zhi > a->coordinates[a->length - 1]->z)
    {
      chl_err_raise (INVALID_ARGUMENT_ERROR,
                     "sta_hi must be less than or equal to last station",
                     __FILE__,
                     __LINE__);
      return NULL;
    }

  double      eps = 1e-10;
  ChlXSArray  sa;
  Coordinate  c0;
  Coordinate  c1;
  Coordinate *array = chl_calloc (a->length, sizeof (Coordinate));

  /* loop variables */
  int i  = find_zlo_idx (a, 0, a->length, zlo);
  i      = find_high_elev (a, i);
  int j  = 0;
  int hi = find_zhi_idx (a, a->length, 0, a->length, zhi);
  hi     = find_high_elev (a, hi);

  c0 = a->coordinates[i];
  c1 = a->coordinates[i + 1];

  if (fabs (c1->z - c0->z) <= eps)
    array[j++] = coord_copy (c0);
  else
    array[j++] = coord_interp_y (c0, c1, zlo);

  while (++i < hi)
    {
      array[j++] = coord_copy (a->coordinates[i]);
    }

  c0 = a->coordinates[i - 1];
  c1 = a->coordinates[i];
  if (fabs (c1->z - c0->z) <= eps)
    array[j++] = coord_copy (c1);
  else
    array[j++] = coord_interp_y (c0, c1, zhi);

  sa = chl_xs_array_from_array (j, array);
  chl_free (array);

  return sa;
}
