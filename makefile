all: hw3

hw3: mainTest.o
ifeq ($(OS),Windows_NT)
	g++ -o hw3 mainTest.o -lgtest
else
	g++ -o hw3 mainTest.o -lgtest -lpthread
endif
mainTest.o: mainTest.cpp struct.h atom.h number.h variable.h utStruct.h utVariable.h
	g++ -std=gnu++0x -c mainTest.cpp
##variable.o: variable.cpp variable.h
##	g++ -std=gnu++0x -c variable.cpp
clean:
	rm -f *.o hw3
stat:
	wc *.h *.cpp
