all: hw2

hw2: mainTerm.o atom.o Number.o variable.o
ifeq ($(OS),Windows_NT)
	g++ -o hw2 mainTerm.o atom.o Number.o variable.o -lgtest
else
	g++ -o hw2 mainTerm.o atom.o Number.o variable.o -lgtest -lpthread
endif
mainTerm.o: mainTerm.cpp Number.h atom.h variable.h utTerm.h
	g++ -std=gnu++0x -c mainTerm.cpp
atom.o: atom.cpp atom.h
	g++ -std=gnu++0x -c atom.cpp
Number.o: Number.cpp Number.h
	g++ -std=gnu++0x -c Number.cpp
variable.o: variable.cpp variable.h
	g++ -std=gnu++0x -c variable.cpp
clean:
	rm -f *.o hw2
stat:
	wc *.h *.cpp
