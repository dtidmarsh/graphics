#include "DVector.h"

DVector2D DVector2DMake(float x, float y)
{
  DVector2D v;
	
  v.vec[0] = x;
  v.vec[1] = y;
	
  return v;
}

DVector3D DVector3DMake(float x, float y, float w)
{
  DVector3D v;
	
  v.vec[0] = x;
  v.vec[1] = y;
  v.vec[2] = w;
	
  return v;
}
