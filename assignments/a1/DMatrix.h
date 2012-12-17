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


DMatrix DMatrixMake(float m11, float m12, float m13, float m21, float m22, 
float m23, float m31, float m32, float m33);

DMatrix DMatrixMakeTranslate(float tx, float ty);
DMatrix DMatrixMakeRotate(float theta);
DMatrix DMatrixMakeScale(float sx, float sy);

// Multiply two 3x3 matrices
DMatrix DMatrixMultiplyMatrix(DMatrix m1, DMatrix m2);

// Multiply a 3x3 matrix and a 3x1 vector
DVector3D DMatrixMultiplyVector(DMatrix m, DVector3D v);

#define DMatrixIdentity DMatrixMake(1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f)

#endif
