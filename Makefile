OBJS = vector3d.cpp grid.cpp cell.cpp mymath.cpp species.cpp

CC = g++

COMPILER_FLAGS = -std=c++11

LINKER_FLAGS = -fopenmp

all : main.cpp $(OBJS)
	$(CC) main.cpp $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o sim

test : test.cpp $(OBJS)
	$(CC) test.cpp $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o test

testPlain : test.cpp
	$(CC) test.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o test
