all: hw5

hw5: mainTest.o number.o atom.o struct.o variable.o list.o
ifeq ($(OS),Windows_NT)
	g++ -o hw5 mainTest.o number.o atom.o struct.o variable.o list.o -lgtest
else
	g++ -o hw5 mainTest.o number.o atom.o struct.o variable.o list.o -lgtest -lpthread
endif
mainTest.o: mainTest.cpp parser.h utParser.h #utStruct.h utVariable.h utList.h
	g++ -std=gnu++0x -c mainTest.cpp
list.o: list.cpp list.h
	g++ -std=gnu++0x -c list.cpp
number.o: number.cpp number.h
	g++ -std=gnu++0x -c number.cpp
atom.o: atom.cpp atom.h
	g++ -std=gnu++0x -c atom.cpp
struct.o: struct.cpp struct.h
	g++ -std=gnu++0x -c struct.cpp
variable.o: variable.cpp variable.h
	g++ -std=gnu++0x -c variable.cpp
clean:
	rm -f *.o hw5
stat:
	wc *.h *.cpp
