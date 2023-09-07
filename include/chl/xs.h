#ifndef CHL_XS_
#define CHL_XS_

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Cross section coordinate
 *
 */
typedef struct
{
  double station;
  double elevation;
} ChXSCoordinate;

/**
 * @brief Cross section coordinate array
 *
 */
typedef struct ChXSCoords ChXSCoords;

/**
 * @brief Cross section subsection
 *
 */
typedef struct ChXSSubsect ChXSSubsect;

/**
 * @brief Allocates
 *
 * @param size Number of coordinates to allocate
 * @return ChXSCoords* Pointer to a new ChXSCoords
 */
extern ChXSCoords *ch_xs_coords_new (size_t size);

extern ChXSCoords *
ch_xs_coords_init (size_t length, double *station, double *elevation);

/**
 * @brief Frees a ChXSCoords
 *
 * @param coords ChXSCoords to free
 */
extern void ch_xs_coords_free (ChXSCoords **coords);

/**
 * @brief Returns the number of coordinates stored in a ChXSCoords
 *
 * @param coords A pointer to a ChXSCoords
 * @return size_t The number of coordinates
 */
extern size_t chl_xs_coords_length (ChXSCoords *coords);

/**
 * @brief Returns a coordinate stored in a ChXSCoords
 *
 * @param coords Pointer to a ChXSCoords
 * @param i The index of the coordinate to return
 * @return ChXSCoordinate Returned coordinate
 */
extern ChXSCoordinate ch_xs_coords_get (ChXSCoords *coords, size_t i);

/**
 * @brief Returns a pointer to a coordinate stored in a ChXSCoords
 *
 * @param coords Pointer to a ChXSCoords
 * @param i The index of the coordinate
 * @return ChXSCoordinate* Pointer to a coordinate
 */
extern ChXSCoordinate *ch_xs_coords_get_ptr (ChXSCoords *coords, size_t i);

/**
 * @brief Sets the values of a coordinate in a ChXSCoords
 *
 * @param coords Pointer to a ChXSCoords
 * @param coord A coordinate containing station, elevation values
 * @param i The index of the coordinate to set
 */
extern void
ch_xs_coords_set (ChXSCoords *coords, ChXSCoordinate coord, size_t i);

#endif
