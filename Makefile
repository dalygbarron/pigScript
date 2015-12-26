CC = g++
FLAGS = -static -std=c++11
LIBS = -L /usr/local/lib/danylib/ -l danylib

assembler: src/*.cc src/assembler/*.cc
	$(CC) $(FLAGS) src/assembler/*.cc src/Script.cc src/Instruction.cc $(LIBS) -o bin/assembler

virtualMachine:
	$(CC) $(FLAGS) src/Instruction.cc $(LIBS) -c
	$(CC) $(FLAGS) src/Script.cc $(LIBS) -c
	$(CC) $(FLAGS) src/VirtualMachine.cc $(LIBS) -c
	ar rcs bin/libpigScript.a *.o
	rm *.o

install: assembler virtualMachine
	#make the directories they go in
	mkdir -p /usr/local/bin/
	mkdir -p /usr/local/lib/pigScript/
	mkdir -p /usr/local/include/pigScript/

	#copy the files over
	cp bin/assembler /usr/local/bin/pigScript/pigScriptAssembler
	cp src/*.hh /usr/local/include/pigScript/
	cp bin/libpigScript.a /usr/local/lib/pigScript/libpigScript.a
