#include <chl.h>
#include <emscripten.h>
#include <stdlib.h>

// creates a new empty matrix
EMSCRIPTEN_KEEPALIVE
ChlMatrix
matrix_new (int n_rows, int n_columns)
{
  return chl_matrix_new (n_rows, n_columns);
}

// creates a new matrix from previously allocated memory
EMSCRIPTEN_KEEPALIVE
ChlMatrix
matrix_new_from (int n_rows, int n_columns, double *entries)
{
  return chl_matrix_new_from (n_rows, n_columns, entries);
}

// creates a new identity matrix
EMSCRIPTEN_KEEPALIVE ChlMatrix
matrix_eye (int n)
{
  return chl_matrix_eye (n);
}

// frees a matrix
EMSCRIPTEN_KEEPALIVE
int
matrix_free (ChlMatrix a)
{
  return chl_matrix_free (a);
}

// returns the number of rows in a matrix
EMSCRIPTEN_KEEPALIVE
int
matrix_rows (ChlMatrix a)
{
  return chl_matrix_rows (a);
}

// returns the number of columns in a matrix
EMSCRIPTEN_KEEPALIVE
int
matrix_cols (ChlMatrix a)
{
  return chl_matrix_cols (a);
}

// returns an entry from a matrix
EMSCRIPTEN_KEEPALIVE
double
matrix_get (ChlMatrix a, int i, int j)
{
  double value;
  chl_matrix_get (a, i, j, &value);
  return value;
}

// sets an entry in a matrix
EMSCRIPTEN_KEEPALIVE
void
matrix_set (ChlMatrix a, int i, int j, double value)
{
  chl_matrix_set (a, i, j, value);
}

// multiplies two matrices
EMSCRIPTEN_KEEPALIVE
void
matrix_mult (ChlMatrix a, ChlMatrix b, ChlMatrix c)
{
  chl_matrix_mult (a, b, &c);
}

// multiply a matrix by a scalar
EMSCRIPTEN_KEEPALIVE
void
matrix_scalar_mult (ChlMatrix a, double c, ChlMatrix b)
{
  chl_matrix_scalar_mult (a, c, &b);
}

// vector dot product
EMSCRIPTEN_KEEPALIVE
double
matrix_dot (ChlMatrix a, ChlMatrix b)
{
  double dot;
  chl_matrix_dot (a, b, &dot);
  return dot;
}

// linear sum of matrices
EMSCRIPTEN_KEEPALIVE
void
matrix_add (ChlMatrix a, ChlMatrix b, ChlMatrix c)
{
  chl_matrix_add (a, b, &c);
}

// transpose of a matrix
EMSCRIPTEN_KEEPALIVE
void
matrix_transpose (ChlMatrix a, ChlMatrix a_t)
{
  chl_matrix_transpose (a, &a_t);
}
