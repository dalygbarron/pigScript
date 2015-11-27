CC = g++
FLAGS = -static -std=c++11 -g
LIBS = -L /usr/local/lib/danylib/ -l danylib

assembler: src/*.cc src/assembler/*.cc
	$(CC) $(FLAGS) src/assembler/*.cc src/Script.cc src/Instruction.cc $(LIBS) -o bin/assembler

pigScriptVanilla: src/*.cc
	$(CC) $(FLAGS) src/*.cc $(LIBS) -o bin/pigScriptVanilla

install: assembler
	echo "this doesn't work yet"
