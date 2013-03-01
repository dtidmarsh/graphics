#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DScene.h"
#include "DRaster.h"

int main(int argc, char* argv[])
{
  FILE* f;
  char c;
  char magicNumber[3];
  int width, height, doneReading;
  float minX, minY, maxX, maxY;
  float r1, g1, b1, r2, g2, b2, r3, g3, b3;
  float tx, ty, theta, sx, sy;
  float temp[9];
	
  if(argc != 2) {
    fprintf(stderr, "Usage: render scene.u2d\n");
    return 1;
  } else if(!(f = fopen(argv[1], "r"))) {
    fprintf(stderr, "Fatal error: Cannot read input scene file.\n");
    return 2;
  } else if(fscanf(f, "%2s", magicNumber) != 1 || strcmp(magicNumber, "U2")) {
    fprintf(stderr, "Fatal error: Incorrect format for input scene file.\n");
    fclose(f);
    return 2;
  } else if(fscanf(f, "%d %d", &width, &height) != 2) {
    fprintf(stderr, "Fatal error: Cannot read scene width/height properly.\n");
    fclose(f);
    return 3;
  }
	
  // check min/max x/y and store them
  if(fscanf(f, "%f %f %f %f", &minX, &minY, &maxX, &maxY) != 4) {
    fprintf(stderr, "Fatal error: Cannot read min/max coordinates properly.\n");
    fclose(f);
    return 3;
  }
	
  DScene scene = DSceneMake(width, height, minX, minY, maxX, maxY);
  DRaster* raster = DRasterMake(width, height, DColorBlack);
	
  doneReading = 0;
  // initialize all colors to black
  r1 = g1 = b1 = r2 = g2 = b2 = r3 = g3 = b3 = 0;

  while(!doneReading) {
    fscanf(f, "%*[ \t\n\f\v\r]");
    c = fgetc(f);
    switch(c)
      {
      case 'g':
	{
	  // geometry line
	  if(scene.gFile[0] != '\0') {
	    // apply most recent geometry to raster
	    DColor aC = DColorMake(1.0f, r1, g1, b1);
	    DColor bC = DColorMake(1.0f, r2, g2, b2);
	    DColor cC = DColorMake(1.0f, r3, g3, b3);
	    DRasterApplyGeometry(raster, scene, aC, bC, cC);

	    // refresh transformation matrix
	    scene.m = DMatrixIdentity;
	  }
	  // get name of new geometry file from input
	  DSceneLoadFilename(&scene, f);
	  break;
	}
			
      case 'c':
	{	
	  // color line
  if(fscanf(f, "%f %f %f %f %f %f %f %f %f", &temp[0], &temp[1],
		    &temp[2], &temp[3], &temp[4], &temp[5], &temp[6],
		    &temp[7], &temp[8]) != 9) {
	    fprintf(stderr, "Error: Invalid format for color instruction.\n");
	    break;
	  } else {
	    while(1) {
	      c = getc(f);
	      if(c == '\n' || c == EOF) {
		r1 = temp[0];
		g1 = temp[1];
		b1 = temp[2];
		r2 = temp[3];
		g2 = temp[4];
		b2 = temp[5];
		r3 = temp[6];
		g3 = temp[7];
		b3 = temp[8];
		break;
	      }
	      else if(!isspace((unsigned char)c)) {
		fprintf(stderr, 
			"Error: Invalid format for color instruction.\n");
		break;
	      }
	    }
	  }
	  break;
	}
			
      case 't':
	{
	  // translate line
	  if(fscanf(f, "%f %f", &temp[0], &temp[1]) != 2) {
	    fprintf(stderr,
		    "Error: Invalid format for transform instruction.\n");
	    break;
	  } else {
	    while(1) {
	      c = getc(f);
	      if(c == '\n' || c == EOF) {
		tx = temp[0];
		ty = temp[1];
		scene.m = DMatrixMultiplyMatrix(scene.m,
						DMatrixMakeTranslate(tx, ty));
		break;
	      }
	      else if(!isspace((unsigned char)c)) {
		fprintf(stderr,
			"Error: Invalid format for transform instruction.\n");
		break;
	      }
	    }
	  }
	  break;
	}
			
      case 'r':
	{	
	  // rotate line
	  if(fscanf(f, "%f", &temp[0]) != 1) {
	    fprintf(stderr, "Error: Invalid format for rotate instruction.\n");
	    break;
	  } else {
	    while(1) {
	      c = getc(f);
	      if(c == '\n' || c == EOF) {
		theta = temp[0];
		scene.m = DMatrixMultiplyMatrix(scene.m,
						DMatrixMakeRotate(theta));
		break;
	      }
	      else if(!isspace((unsigned char)c)) {
		fprintf(stderr,
			"Error: Invalid format for rotate instruction.\n");
		break;
	      }
	    }
	  }
	  break;
	}
			
      case 's':
	{
	  // scale line
	  if(fscanf(f, "%f %f", &temp[0], &temp[1]) != 2) {
	    fprintf(stderr, "Error: Invalid format for scale instruction.\n");
	    break;
	  } else {
	    while(1) {
	      c = getc(f);
	      if(c == '\n' || c == EOF) {
		sx = temp[0];
		sy = temp[1];
		scene.m = DMatrixMultiplyMatrix(scene.m,
						DMatrixMakeScale(sx, sy));
		break;
	      }
	      else if(!isspace((unsigned char)c)) {
		fprintf(stderr,
			"Error: Invalid format for scale instruction.\n");
		break;
	      }
	    }
	  }
	  break;
	}
			
      case EOF:
	{
	  if(scene.gFile[0] != '\0') {
	    // apply most recent geometry to raster
	    DColor aC = DColorMake(1.0f, r1, g1, b1);
	    DColor bC = DColorMake(1.0f, r2, g2, b2);
	    DColor cC = DColorMake(1.0f, r3, g3, b3);
	    DRasterApplyGeometry(raster, scene, aC, bC, cC);
	  }

	  doneReading = 1;
	  break;
	}
				
      default:
	{
	  fprintf(stderr,
		  "Error: Unrecognized instruction for triangle transformation.\n");
	  while((c = fgetc(f)) != '\n' && c != EOF);
	  break;
	}	
      }
  }
	
  DRasterSavePPM(raster, "scene.ppm");
  DRasterSaveBMP(raster, "scene.bmp");
	
  // cleanup
  fclose(f);
  free(scene.gFile);
  DRasterDestroy(raster);
	
  return 0;
}
