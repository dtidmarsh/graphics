#ifndef DMATRIX_H
#define DMATRIX_H

#include "DVector.h"

/*
  DMatrix structure implements a 3x3 matrix
  class to represent the desired geometry
  transformations (translate, scale, rotate).
	
  mat: 2D array of floats to hold the nine
  elements of the matrix. Row-major.
	
*/
typedef struct DMatrix
{
  float mat[3][3];
} DMatrix;


// Constructor
DMatrix DMatrixMake(float m11, float m12, float m13, float m21, float m22, 
		    float m23, float m31, float m32, float m33);

// Creates translation matrix
DMatrix DMatrixMakeTranslate(float tx, float ty);

// Creates rotation matrix
DMatrix DMatrixMakeRotate(float theta);

// Creates scale matrix
DMatrix DMatrixMakeScale(float sx, float sy);

// Multiply two matrices
DMatrix DMatrixMultiplyMatrix(DMatrix m1, DMatrix m2);

// Multiply a matrix and a 3D vector
DVector3D DMatrixMultiplyVector(DMatrix m, DVector3D v);

// Macro for identity matrix constructor
#define DMatrixIdentity DMatrixMake(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f)

#endif
