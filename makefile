all: hw2

hw2: main.o number.o atom.o variable.o 
ifeq (${OS}, Windows_NT)
	g++ -o hw2 main.o number.o atom.o variable.o -lgtest
else
	g++ -o hw2 main.o number.o atom.o variable.o -lgtest -lpthread
endif

main.o: main.cpp utTerm.h
	g++ -std=gnu++0x -c main.cpp
number.o: number.h number.cpp
	g++ -std=gnu++0x -c number.cpp
atom.o: atom.h atom.cpp
	g++ -std=gnu++0x -c atom.cpp
variable.o: variable.h variable.cpp
	g++ -std=gnu++0x -c variable.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif

