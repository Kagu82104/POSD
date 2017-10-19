all: hw3

hw3: mainTest.o number.o atom.o struct.o variable.o
ifeq ($(OS),Windows_NT)
	g++ -o hw3 mainTest.o number.o atom.o struct.o variable.o -lgtest
else
	g++ -o hw3 mainTest.o number.o atom.o struct.o variable.o -lgtest -lpthread
endif
mainTest.o: mainTest.cpp utStruct.h utVariable.h
	g++ -std=gnu++0x -c mainTest.cpp
number.o: number.cpp number.h
	g++ -std=gnu++0x -c number.cpp
atom.o: atom.cpp atom.h
	g++ -std=gnu++0x -c atom.cpp
struct.o: struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp
variable.o: variable.cpp variable.h
	g++ -std=gnu++0x -c variable.cpp
clean:
	rm -f *.o hw3
stat:
	wc *.h *.cpp
