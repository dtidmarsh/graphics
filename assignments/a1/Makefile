CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic
OBJECTS=main.o DScene.o DMatrix.o DVector.o DTriangle.o DColor.o DRaster.o


render: $(OBJECTS)
	$(CC) $(CFLAGS) -lm -o $@ -O3 -g $(OBJECTS)
	rm $(OBJECTS)

%.o: %.h

clean:
	rm -f render* $(OBJECTS)