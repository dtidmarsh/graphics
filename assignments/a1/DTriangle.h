#ifndef DTRIANGLE_H
#define DTRIANGLE_H

#include "DVector.h"

/*
  DTriangle structure consists of a
  triangle represented as a collection
  of 3 2x1 vectors.	
*/

typedef struct DTriangle {
  DVector2D a, b, c;
} DTriangle;

DTriangle DTriangleMake(DVector2D a, DVector2D b, DVector2D c);

// Calculate barycentric coordinates
void DTriangleBarycentric(DTriangle t, DVector2D v, float* lambda1, float* lambda2, float* lambda3);
	
#endif
