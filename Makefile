CXXFLAGS = -g -O3 -Wall -Wextra -Wuninitialized -pedantic -std=c++14

#OBJS =   main  AllTest
#OBJS = NodeTest
OBJS = ForestTest main AllTest

all: ${OBJS}

ForestTest: Forest.o Advance.o Node.o
NodeTest: Node.o Advance.o
main: Forest.o Node.o Advance.o
AllTest: Forest.o Node.o Advance.o

all: ${OBJS}

Advance.o: Advance.h
Node.o: Node.h Advance.h 

Forest.o: Forest.h Node.h Advance.h

clean:
	rm -f ${OBJS} *.o

memcheck: main
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./main
