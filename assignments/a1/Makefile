CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -I.

OBJECTS=main.o DScene.o DMatrix.o DVector.o DTriangle.o DColor.o DRaster.o

render: $(OBJECTS)
	$(CC) $(CFLAGS) -lm -o render -g $(OBJECTS)
	rm $(OBJECTS)

clean:
	rm -f render*