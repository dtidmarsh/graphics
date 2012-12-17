#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "DMatrix.h"

DMatrix DMatrixMake(float m11, float m12, float m13, float m21, float m22, 
float m23, float m31, float m32, float m33)
{
  DMatrix m;
	
  m.mat[0][0] = m11;
  m.mat[0][1] = m12;
  m.mat[0][2] = m13;
	
  m.mat[1][0] = m21;
  m.mat[1][1] = m22;
  m.mat[1][2] = m23;
	
  m.mat[2][0] = m31;
  m.mat[2][1] = m32;
  m.mat[2][2] = m33;
	
  return m;
}

DMatrix DMatrixMakeTranslate(float tx, float ty)
{
  DMatrix m;
	
  m.mat[0][0] = 1.0f;
  m.mat[0][1] = 0.0f;
  m.mat[0][2] = tx;
	
  m.mat[1][0] = 0.0f;
  m.mat[1][1] = 1.0f;
  m.mat[1][2] = ty;
	
  m.mat[2][0] = 0.0f;
  m.mat[2][1] = 0.0f;
  m.mat[2][2] = 1.0f;
	
  return m;
}

DMatrix DMatrixMakeRotate(float theta)
{
  float cosT = cosf(theta);
  float sinT = sinf(theta);
	
  DMatrix m;
	
  m.mat[0][0] = cosT;
  m.mat[0][1] = -sinT;
  m.mat[0][2] = 0.0f;
	
  m.mat[1][0] = sinT;
  m.mat[1][1] = cosT;
  m.mat[1][2] = 0.0f;
	
  m.mat[2][0] = 0.0f;
  m.mat[2][1] = 0.0f;
  m.mat[2][2] = 1.0f;
	
  return m;
}

DMatrix DMatrixMakeScale(float sx, float sy)
{
  DMatrix m;
	
  m.mat[0][0] = sx;
  m.mat[0][1] = 0.0f;
  m.mat[0][2] = 0.0f;
	
  m.mat[1][0] = 0.0f;
  m.mat[1][1] = sy;
  m.mat[1][2] = 0.0f;
	
  m.mat[2][0] = 0.0f;
  m.mat[2][1] = 0.0f;
  m.mat[2][2] = 1.0f;
	
  return m;
}

DMatrix DMatrixMultiplyMatrix(DMatrix m1, DMatrix m2)
{
  DMatrix m;
	
  m.mat[0][0] = m1.mat[0][0]*m2.mat[0][0] + m1.mat[0][1]*m2.mat[1][0]
    + m1.mat[0][2]*m2.mat[2][0];
  m.mat[0][1] = m1.mat[0][0]*m2.mat[0][1] + m1.mat[0][1]*m2.mat[1][1]
    + m1.mat[0][2]*m2.mat[2][1];
  m.mat[0][2] = m1.mat[0][0]*m2.mat[0][2] + m1.mat[0][1]*m2.mat[1][2]
    + m1.mat[0][2]*m2.mat[2][2];
	
  m.mat[1][0] = m1.mat[1][0]*m2.mat[0][0] + m1.mat[1][1]*m2.mat[1][0]
    + m1.mat[1][2]*m2.mat[2][0];
  m.mat[1][1] = m1.mat[1][0]*m2.mat[0][1] + m1.mat[1][1]*m2.mat[1][1]
    + m1.mat[1][2]*m2.mat[2][1];
  m.mat[1][2] = m1.mat[1][0]*m2.mat[0][2] + m1.mat[1][1]*m2.mat[1][2]
    + m1.mat[1][2]*m2.mat[2][2];
	
  m.mat[2][0] = m1.mat[2][0]*m2.mat[0][0] + m1.mat[2][1]*m2.mat[1][0]
    + m1.mat[2][2]*m2.mat[2][0];
  m.mat[2][1] = m1.mat[2][0]*m2.mat[0][1] + m1.mat[2][1]*m2.mat[1][1]
    + m1.mat[2][2]*m2.mat[2][1];
  m.mat[2][2] = m1.mat[2][0]*m2.mat[0][2] + m1.mat[2][1]*m2.mat[1][2]
    + m1.mat[2][2]*m2.mat[2][2];
	
  return m;
}

DVector3D DMatrixMultiplyVector(DMatrix m, DVector3D v)
{
  DVector3D v1;
	
  v1.vec[0] = m.mat[0][0]*v.vec[0] + m.mat[0][1]*v.vec[1]
    + m.mat[0][2]*v.vec[2];
  v1.vec[1] = m.mat[1][0]*v.vec[0] + m.mat[1][1]*v.vec[1]
    + m.mat[1][2]*v.vec[2];
  v1.vec[2] = m.mat[2][0]*v.vec[0] + m.mat[2][1]*v.vec[1]
    + m.mat[2][2]*v.vec[2];
	
  return v1;
}
