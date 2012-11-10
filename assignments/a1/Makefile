CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic

OBJECTS=main.o DScene.o DMatrix.o DVector.o DTriangle.o DColor.o DRaster.o

render: $(OBJECTS)
	$(CC) $(CFLAGS) -lm -o render -O3 -g $(OBJECTS)
	rm $(OBJECTS)

clean:
	rm -f render*