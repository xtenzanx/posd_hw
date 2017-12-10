all: hw7
 
hw7: main.o term.o atom.o struct.o list.o

ifeq (${OS}, Windows_NT)
	g++ -o hw7 main.o term.o atom.o struct.o list.o -lgtest
else
	g++ -o hw7 main.o term.o atom.o struct.o list.o -lgtest -lpthread
endif

main.o: main.cpp variable.h global.h parser.h
	g++ -std=gnu++0x -c main.cpp
term.o: term.cpp term.h 
	g++ -std=gnu++0x -c term.cpp
atom.o: atom.cpp atom.h 
	g++ -std=gnu++0x -c atom.cpp
struct.o: struct.cpp struct.h 
	g++ -std=gnu++0x -c struct.cpp
list.o: list.cpp list.h 
	g++ -std=gnu++0x -c list.cpp

clean:
	rm -f *.o hw7
stat:
	wc *.h *.cpp