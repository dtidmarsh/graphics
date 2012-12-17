#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DScene.h"

DScene DSceneMake(int width, int height, float minX, float minY, float maxX, 
float maxY)
{
  DScene s;
  
  s.m = DMatrixIdentity;
  s.width = width;
  s.height = height;
  s.minX = minX;
  s.minY = minY;
  s.maxX = maxX;
  s.maxY = maxY;
  s.gFile = malloc(sizeof(char) * INIT_SIZE);
  if(s.gFile == NULL) {
    fprintf(stderr, "Error allocating memory for DScene.gFile.\n");
    exit(1);
  }
  s.gFile[0] = '\0';
  s.buffSize = INIT_SIZE;
  
  return s;
}

int DSceneGetWidth(DScene s)
{
  return s.width;
}

int DSceneGetHeight(DScene s)
{
  return s.height;
}


void DSceneLoadFilename(DScene* s, FILE* f)
{
  int len;
  len = 0;
  
  // eliminate whitespace after 'g' char
  fscanf(f, "%*[ \n\t\r\f\v]");
  
  /* Increase size of buffer until whole filename has been read.
     Prevents buffer overflow for absurdly long filenames. */
  while(fgets(&s->gFile[len], INIT_SIZE, f) != 0 && 
	s->gFile[(len = strlen(s->gFile)) - 1] != '\n') {
    s->gFile = realloc(s->gFile, strlen(s->gFile) + (sizeof(char)*INIT_SIZE));
    s->buffSize += INIT_SIZE;
  }
  
  // add null terminator to end of filename
  if(s->gFile[len - 1] == '\n') {
    s->gFile[len - 1] = '\0';
  } else if(len < s->buffSize) {
    s->gFile[len] = '\0';
  } else {
    s->gFile = realloc(s->gFile, len + sizeof(char));
    s->gFile[len] = '\0';
  }
  
  return;
}
