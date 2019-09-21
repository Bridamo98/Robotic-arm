CXXFLAGS := -std=c++11 -g
LIBS := -lm -lGL -lGLU -lglut
HEADERS := Vector.h Camera.h Mesh.h SpatialObject.h
OBJS := SolarSystem.o Vector.o Camera.o Mesh.o SpatialObject.o

all: SolarSystem

SolarSystem: $(OBJS) $(HEADERS)
	g++ $(CXXFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.cxx
	g++ $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -r *.o SolarSystem

## eof - Makefile
