CC = g++
FLAGS = -std=c++11

assembler: src/assembler/*.cc
	$(CC) $(FLAGS) src/*.cc src/assembler/*.cc -o bin/assembler
