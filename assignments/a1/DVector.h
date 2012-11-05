#ifndef DVECTOR_H
#define DVECTOR_H

/*
  DVector structure implements 2D and 
  3D vector classes to represent the
  result of matrix transformation.
	
  vec: 1D 2- or 3-element array that
  holds x/y (and 3D w) coordinates.
*/
typedef struct DVector2D {
  float vec[2];
} DVector2D;

typedef struct DVector3D {
  float vec[3];
} DVector3D;

// Constructors
DVector2D DVector2DMake(float x, float y);
DVector3D DVector3DMake(float x, float y, float w);

#endif
