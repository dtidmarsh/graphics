#include <stdlib.h>
#include "DTriangle.h"

DTriangle DTriangleMake(DVector2D a, DVector2D b, DVector2D c)
{
  DTriangle t;
	
  t.a = a;
  t.b = b;
  t.c = c;
	
  return t;
}

void DTriangleBarycentric(DTriangle t, DVector2D v, float* lambda1, float* lambda2, float* lambda3)
{
  float lam1, lam2;
  float y2_y3, x_x3, x3_x2, y_y3, y3_y1, x1_x3, denom;
	
  // semi-optimized calculations
  y2_y3 = t.b.vec[1] - t.c.vec[1];
  x_x3 = v.vec[0] - t.c.vec[0];
  x3_x2 = t.c.vec[0] - t.b.vec[0];
  y_y3 = v.vec[1] - t.c.vec[1];
  y3_y1 = t.c.vec[1] - t.a.vec[1];
  x1_x3 = t.a.vec[0] - t.c.vec[0];
  denom = ((y2_y3*x1_x3) + ((t.c.vec[0] - t.b.vec[0])*(t.a.vec[1] - t.c.vec[1])));

  if(lambda1 != NULL) *lambda1 = (lam1 = (y2_y3*x_x3 + x3_x2*y_y3)/denom);
  if(lambda2 != NULL) *lambda2 = (lam2 = (y3_y1*x_x3 + x1_x3*y_y3)/denom);
  if(lambda3 != NULL) *lambda3 = 1.0f - lam1 - lam2;
}
