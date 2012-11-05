#ifndef DCOLOR_H
#define DCOLOR_H

#include <stdint.h>

// Integer representation of colors
typedef uint32_t DColorARGB;

// Floating-point representation of colors
typedef float ColorChannel;

/*
  DColor structure represents ARGB color
  values as 4 channels, each a floating
  point number.
*/
typedef struct DColor {
  ColorChannel a, r, g, b;
} DColor;

// Constructor
DColor DColorMake(ColorChannel a, ColorChannel r, ColorChannel g, ColorChannel b);

// Convert DColor to DColorARGB (for file output)
DColorARGB DColorToARGB(DColor c);

// Add and scale operations
DColor DColorAdd(DColor c1, DColor c2);
DColor DColorScale(DColor c, float lambda);

// DColorBlack: macro for constructing black DColor
#define DColorBlack DColorMake(1.0f, 0.0f, 0.0f, 0.0f)

#endif
