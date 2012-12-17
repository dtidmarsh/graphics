#include <math.h>
#include "DColor.h"

DColor DColorMake(ColorChannel a, ColorChannel r, ColorChannel g, 
ColorChannel b)
{
  DColor c;
	
  c.a = a;
  c.r = r;
  c.g = g;
  c.b = b;
	
  return c;
}

DColorARGB DColorToARGB(DColor c)
{
  DColorARGB color;
	
  color = (((DColorARGB)floorf(c.a * 255.0f) << 24) |
	   ((DColorARGB)floorf(c.r * 255.0f) << 16) |
	   ((DColorARGB)floorf(c.g * 255.0f) << 8) |
	   ((DColorARGB)floorf(c.b * 255.0f)));
			
  return color;
}

DColor DColorAdd(DColor c1, DColor c2)
{
  DColor c;
	
  c.a = c1.a + c2.a;
  c.r = c1.r + c2.r;
  c.g = c1.g + c2.g;
  c.b = c1.b + c2.b;
	
  return c;
}

DColor DColorScale(DColor c, float lambda)
{
  DColor c1;
	
  c1.a = c.a * lambda;
  c1.r = c.r * lambda;
  c1.g = c.g * lambda;
  c1.b = c.b * lambda;
	
  return c1;
}
