CC = g++
FLAGS = -static -std=c++11
LIBS = -L /usr/local/lib/danylib/ -l danylib

assembler: src/assembler/*.cc
	$(CC) $(FLAGS) src/*.cc src/assembler/*.cc $(LIBS) -o bin/assembler

install: assembler
	echo "this doesn't work yet"
