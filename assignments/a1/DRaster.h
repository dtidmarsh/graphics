#ifndef DRASTER_H
#define DRASTER_H

#include "DColor.h"
#include "DMatrix.h"
#include "DScene.h"
#include "DTriangle.h"

/*
  DRaster structure holds the raster data
  in memory.
	
  width, height: ints denoting raster size.
  pixels: pointer to 1D array of pixels
  represented as DColors (4 floats).
*/

typedef struct DRaster {
  int width, height;
  DColor* pixels;
} DRaster;

DRaster* DRasterMake(int width, int height, DColor fill);

// Getters for raster width/height
int DRasterWidth(DRaster* raster);
int DRasterHeight(DRaster* raster);

// Methods for drawing triangle (filled and interpolated)
void DRasterDrawTriangle(DRaster* raster, DTriangle t, DColor fill);
void DRasterDrawTriangleInterp(DRaster* raster, DTriangle t, DColor aC, DColor bC, DColor cC);

// Applies most recent geometry information to raster
int DRasterApplyGeometry(DRaster* raster, DScene s, DColor aC, DColor bC, DColor cC);

void DRasterSavePPM(DRaster* raster, char* path);
void DRasterSaveBMP(DRaster* raster, char* path);

void DRasterDestroy(DRaster* raster);

#endif
