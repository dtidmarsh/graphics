#ifndef DSCENE_H
#define DSCENE_H

// Initial size of filename buffer
#define INIT_SIZE (1000)

#include "DMatrix.h"

/*
  DScene structure holds information about a given
  scene file.
	
  m: Transformation matrix representing the
  combination of all desired transforms.

  gFile: The most recent geometry file specified by
  a "g" line.

  width, height: The width and height of the raster.

  buffSize: The size of the buffer for the geometry
  file.

  minX, minY, maxX, maxY: The minimum and maximum
  values of the x and y coordinates of the raster.
*/
typedef struct DScene {
  DMatrix m;
  char* gFile;
  int width, height, buffSize;
  float minX, minY, maxX, maxY;
} DScene;

DScene DSceneMake(int width, int height, float minX, float minY, float maxX, float maxY);

int DSceneGetWidth(DScene s);
int DSceneGetHeight(DScene s);

// Store filename from file
void DSceneLoadFilename(DScene* s, FILE* f);

#endif
