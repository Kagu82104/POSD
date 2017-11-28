all: hw6
atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp
utVariable: mainVariable.o atom.o
		g++ -o utVariable mainVariable.o atom.o -lgtest -lpthread
hw6: mainScanner.o atom.o list.o scanner.h utScanner.h utParser.h parser.h node.h
ifeq ($(OS),Windows_NT)
	g++ -o hw6 mainScanner.o atom.o list.o scanner.h utScanner.h utParser.h parser.h node.h -lgtest
else
	g++ -o hw6 mainScanner.o atom.o list.o scanner.h utScanner.h utParser.h parser.h node.h -lgtest -lpthread
endif
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h node.h
		g++ -std=gnu++0x -c mainScanner.cpp
clean:
	rm -f *.o madRace utAtom utVariable utScanner hw6
stat:
	wc *.h *.cpp
