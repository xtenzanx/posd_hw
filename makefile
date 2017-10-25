all: hw4

hw4: main.o term.o atom.o number.o variable.o struct.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 main.o term.o atom.o number.o variable.o struct.o list.o -lgtest
else
	g++ -o hw4 main.o term.o atom.o number.o variable.o struct.o list.o -lgtest -lpthread
endif
	
main.o: main.cpp utVariable.h utStruct.h utList.h
	g++ -std=gnu++0x -c main.cpp
term.o: term.h term.cpp
	g++ -std=gnu++0x -c term.cpp
number.o: number.h number.cpp
	g++ -std=gnu++0x -c number.cpp
variable.o: variable.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp
atom.o: atom.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp
struct.o: struct.h struct.cpp
	g++ -std=gnu++0x -c struct.cpp
list.o: list.h list.cpp
	g++ -std=gnu++0x -c list.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif

