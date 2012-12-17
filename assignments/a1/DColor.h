#ifndef DCOLOR_H
#define DCOLOR_H

#include <stdint.h>

// Integer representation of colors
typedef uint32_t DColorARGB;

// Floating-point representation of colors
typedef float ColorChannel;

/*
  DColor structure represents ARGB color values as 4 channels, each a floating-
  point number between 0 and 1.
*/
typedef struct DColor {
  ColorChannel a, r, g, b;
} DColor;

DColor DColorMake(ColorChannel a, ColorChannel r, ColorChannel g,
ColorChannel b);

/*
  Convert DColor struct to DColorARGB integer representation (for file output).
  Each channel is scaled to an 8-bit color 0 ... 255, then all are combined.
*/
DColorARGB DColorToARGB(DColor c);

DColor DColorAdd(DColor c1, DColor c2);
DColor DColorScale(DColor c, float lambda);

/*
  DColorBlack: macro for constructing black DColor.
  Used for raster background.
*/
#define DColorBlack DColorMake(1.0f, 0.0f, 0.0f, 0.0f)

#endif
