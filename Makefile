OBJS = vector3d.cpp grid.cpp cell.cpp mymath.cpp species.cpp sim.cpp sim1d.cpp cube.cpp

CC = g++

COMPILER_FLAGS = -std=c++11

LINKER_FLAGS = -fopenmp -lfftw3 -lm

all : main.cpp $(OBJS)
	$(CC) main.cpp $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o sim

test : test.cpp $(OBJS)
	$(CC) test.cpp $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o test

testPlain : test.cpp
	$(CC) test.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o test
