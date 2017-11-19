CXXFLAGS = -g -O3 -Wall -Wextra -Wuninitialized -pedantic -std=c++14
CC=g++ # got weird errors without this...?

#OBJS =   main  AllTest
#OBJS = NodeTest
OBJS = ForestTest main AllTest NodeTest

all: ${OBJS}

ForestTest: Forest.o Advance.o Node.o NodeTester.o
NodeTest: NodeTester.o Node.o Advance.o
main: Forest.o Node.o Advance.o
AllTest: Forest.o Node.o Advance.o

all: ${OBJS}

Advance.o: Advance.h
Node.o: Node.h Advance.h
NodeTester.o: Node.o

Forest.o: Forest.h Node.h Advance.h

clean:
	rm -f ${OBJS} *.o

memcheck: ${OBJS}
	for i in ${OBJS};\
		do valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$$i;\
	done 

test:
	for i in ${OBJS};\
		do ./$$i;\
	done 
