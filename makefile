all: hw6
 
hw6: main.o Atom.o list.o

ifeq (${OS}, Windows_NT)
	g++ -o hw6 main.o Atom.o list.o -lgtest
else
	g++ -o hw6 main.o Atom.o list.o -lgtest -lpthread
endif

main.o: main.cpp variable.h struct.h global.h parser.h
	g++ -std=gnu++0x -c main.cpp
Atom.o: Atom.cpp atom.h 
	g++ -std=gnu++0x -c Atom.cpp
list.o: list.cpp list.h 
	g++ -std=gnu++0x -c list.cpp

clean:
	rm -f *.o hw6
stat:
	wc *.h *.cpp