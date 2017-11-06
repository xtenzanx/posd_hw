all: hw5
 
hw5: main.o Atom.o

ifeq (${OS}, Windows_NT)
	g++ -o hw5 main.o Atom.o -lgtest
else
	g++ -o hw5 main.o Atom.o -lgtest -lpthread
endif

main.o: main.cpp term.h number.h variable.h struct.h list.h global.h parser.h
	g++ -std=gnu++0x -c main.cpp
Atom.o: Atom.cpp atom.h 
	g++ -std=gnu++0x -c Atom.cpp

clean:
	rm -f *.o hw5
stat:
	wc *.h *.cpp