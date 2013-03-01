#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "DRaster.h"

DRaster* DRasterMake(int width, int height, DColor fill)
{
  int i;
  int size = width * height;
  DRaster* raster = malloc(sizeof(DRaster));
	
  raster->width = width;
  raster->height = height;
  raster->pixels = malloc(sizeof(DColor) * size);
	
  for(i = 0; i < size; i++) {
    raster->pixels[i] = fill;
  }
	
  return raster;
}

int DRasterWidth(DRaster* raster)
{
  return raster->width;
}

int DRasterHeight(DRaster* raster)
{
  return raster->height;
}

void DRasterDrawTriangle(DRaster* raster, DTriangle t, DColor fill)
{
  int x, y;
  int width = DRasterWidth(raster);
  int height = DRasterHeight(raster);
  for(y = 0; y < height; y++) {
    for(x = 0; x < width; x++) {
      // calculate barycentric coordinates
      float lambda1 = 0.0f;
      float lambda2 = 0.0f;
      float lambda3 = 0.0f;
      DVector2D v = DVector2DMake((float)x, (float)y);
      DTriangleBarycentric(t, v, &lambda1, &lambda2, &lambda3);
			
      // validate barycentric coordinates and figure out whether to fill pixel
      if(lambda1 >= 0.0f && lambda2 >= 0.0f && lambda3 >= 0.0f) {
	raster->pixels[y * width + x] = fill;
      }
    }
  }
}

void DRasterDrawTriangleInterp(DRaster* raster, DTriangle t, DColor aC,
DColor bC, DColor cC)
{
  int x, y;
  int width = DRasterWidth(raster);
  int height = DRasterHeight(raster);

  for(y = 0; y < height; y++) {
    for(x = 0; x < width; x++) {
      /* find a position on the pixel to represent the whole pixel
	 (center sampling) */
      DVector2D v = DVector2DMake((float)x + 0.5f, (float)y + 0.5f);
			
      // calculate barycentric coordinates
      float lambda1 = 0.0f;
      float lambda2 = 0.0f;
      float lambda3 = 0.0f;
      DTriangleBarycentric(t, v, &lambda1, &lambda2, &lambda3);
			
      // validate barycentric coordinates and figure out whether to fill pixel
      if(lambda1 >= 0.0f && lambda2 >= 0.0f && lambda3 >= 0.0f) {
	DColor aContrib = DColorScale(aC, lambda1);
	DColor bContrib = DColorScale(bC, lambda2);
	DColor cContrib = DColorScale(cC, lambda3);
	DColor color = DColorAdd(aContrib, DColorAdd(bContrib, cContrib));
	raster->pixels[y * width + x] = color;
      }
    }
  }
}

int DRasterApplyGeometry(DRaster* raster, DScene scene, DColor aC, DColor bC,
DColor cC)
{
  DTriangle t;
  DVector3D avec, bvec, cvec;
  FILE* f;
  char c;
  float x1, y1, x2, y2, x3, y3;
  float sceneXSize, sceneYSize;
  float temp[9];
	
  // calculate range of input coordinates
  sceneXSize = fabs(scene.minX) + fabs(scene.maxX);
  sceneYSize = fabs(scene.minY) + fabs(scene.maxY);
	
  if(!(f = fopen(scene.gFile, "r"))) {
    fprintf(stderr, "Error: Cannot read RAW file %s.\n", scene.gFile);
    return 1;
  }
	
  while((c = fgetc(f)) != EOF) {
    ungetc(c, f);
    if(fscanf(f, "%f %f %f %f %f %f %f %f %f", &temp[0], &temp[1], &temp[2],
	      &temp[3], &temp[4], &temp[5], &temp[6], &temp[7], 
	      &temp[8]) != 9) {
      fprintf(stderr, "Error: Invalid format for RAW triangle instruction.\n");
      break;
    } else {
      while(1) {
	c = getc(f);
	if(c == '\n' || c == EOF) {
	  // we ignore temp[2|5|8], as we only deal with 2D coordinates
	  x1 = temp[0];
	  y1 = temp[1];
	  x2 = temp[3];
	  y2 = temp[4];
	  x3 = temp[6];
	  y3 = temp[7];
	  
	  // multiply transformation matrix by three coordinate vectors
	  avec = DMatrixMultiplyVector(scene.m, DVector3DMake(x1, y1, 1));
	  bvec = DMatrixMultiplyVector(scene.m, DVector3DMake(x2, y2, 1));
	  cvec = DMatrixMultiplyVector(scene.m, DVector3DMake(x3, y3, 1));
		
	  // scale vectors to raster coordinates
	  avec.vec[0] = (avec.vec[0] - scene.minX)*
	    ((float)scene.width/sceneXSize);
	  bvec.vec[0] = (bvec.vec[0] - scene.minX)*
	    ((float)scene.width/sceneXSize);
	  cvec.vec[0] = (cvec.vec[0] - scene.minX)*
	    ((float)scene.width/sceneXSize);

	  avec.vec[1] = (float)scene.height - 
	    (avec.vec[1] - scene.minY)*((float)scene.height/sceneYSize);
	  bvec.vec[1] = (float)scene.height -
	    (bvec.vec[1] - scene.minY)*((float)scene.height/sceneYSize);
	  cvec.vec[1] = (float)scene.height -
	    (cvec.vec[1] - scene.minY)*((float)scene.height/sceneYSize);
		
	  t.a = DVector2DMake(avec.vec[0], avec.vec[1]);
	  t.b = DVector2DMake(bvec.vec[0], bvec.vec[1]);
	  t.c = DVector2DMake(cvec.vec[0], cvec.vec[1]);
	  
	  // draw triangle with interpolated colors
	  DRasterDrawTriangleInterp(raster, t, aC, bC, cC);
	  break;
	} else if(!isspace((unsigned char)c)) {
	  /* If there's anything except whitespace after the numbers entered,
	     then it's an invalid format. */
	  fprintf(stderr, "Error: Invalid format for RAW triangle instruction.\n");
	  while((c = fgetc(f)) != '\n' && c != EOF);
	  break;
	}
      }
	    
    }
  }
	
  fclose(f);
  return 0;
}

void DRasterSavePPM(DRaster* raster, char* path)
{
  int width = DRasterWidth(raster);
  int height = DRasterHeight(raster);
	
  // open a file for writing
  FILE* f = fopen(path, "w");
  if(f == NULL) {
    fprintf(stderr, "Error: Cannot open file %s for writing.\n", path);
    fclose(f);
    return;
  }

  // write out information required by plain PPM header definition
  fprintf(f, "P3\n");
  fprintf(f, "%i %i\n", width, height);
  fprintf(f, "%i\n", 255);

  DColor* pixels = raster->pixels;
  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      DColor c = *pixels;
      DColorARGB argb = DColorToARGB(c);
      fprintf(f, "%d %d %d\t", ((argb & 0xFF0000) >> 16),
	      ((argb & 0xFF00) >> 8), (argb & 0xFF));
      pixels++;
    }
    fprintf(f, "\n");
  }
	
  fclose(f);
}

void DRasterSaveBMP(DRaster* raster, char* path)
{	
  // open file for writing binary
  FILE* file = fopen(path, "wb");
  if(file == NULL) {
    fprintf(stderr, "Error: Cannot open file %s for writing.\n", path);
    fclose(file);
    return;
  }
    
  // define header data
  uint16_t magicNumber = 0x4D42;
  uint16_t reserved0 = 0; //0x4D41
  uint16_t reserved1 = 0; //0x5454
  uint32_t dataOffset = 54;
  uint32_t infoHeaderSize = 40;
  uint32_t width = (uint32_t)raster->width;
  uint32_t height = (uint32_t)raster->height;
  uint16_t colorPlanes = 1;
  uint16_t bitsPerPixel = 32;
  uint32_t compression = 0;
  uint32_t dataSize = width * height * bitsPerPixel / 8;
  uint32_t horizontalResolution = 2835;
  uint32_t verticalResolution = 2835;
  uint32_t paletteColorCount = 0;
  uint32_t importantPaletteColorCount = 0;
  uint32_t fileSize = 54 + dataSize;
    
  fwrite(&magicNumber, sizeof(magicNumber), 1, file);
  fwrite(&fileSize, sizeof(fileSize), 1, file);
  fwrite(&reserved0, sizeof(reserved0), 1, file);
  fwrite(&reserved1, sizeof(reserved1), 1, file);
  fwrite(&dataOffset, sizeof(dataOffset), 1, file);
  fwrite(&infoHeaderSize, sizeof(infoHeaderSize), 1, file);
  fwrite(&width, sizeof(width), 1, file);
  fwrite(&height, sizeof(height), 1, file);
  fwrite(&colorPlanes, sizeof(colorPlanes), 1, file);
  fwrite(&bitsPerPixel, sizeof(bitsPerPixel), 1, file);
  fwrite(&compression, sizeof(compression), 1, file);
  fwrite(&dataSize, sizeof(dataSize), 1, file);
  fwrite(&horizontalResolution, sizeof(horizontalResolution), 1, file);
  fwrite(&verticalResolution, sizeof(verticalResolution), 1, file);
  fwrite(&paletteColorCount, sizeof(paletteColorCount), 1, file);
  fwrite(&importantPaletteColorCount, 
	 sizeof(importantPaletteColorCount), 1, file);
	
  for(int y = height - 1; y >= 0; y--) {
    for(unsigned int x = 0; x < width; x++) {
      DColor c = raster->pixels[y * width + x];
      DColorARGB color = DColorToARGB(c);
      fwrite(&color, sizeof(color), 1, file);
    }
  }

  fclose(file);
}

void DRasterDestroy(DRaster* raster)
{
  free(raster->pixels);
  free(raster);
}
