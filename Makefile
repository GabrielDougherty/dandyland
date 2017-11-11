CXXFLAGS = -g -O3 -Wall -Wextra -Wuninitialized -pedantic -std=c++14

#OBJS =   main  AllTes
OBJS = simplemain


all: ${OBJS}

simplemain: Node.o Advance.o
main: Forest.o Node.o Advance.o
AllTest: Forest.o Node.o Advance.o

all: ${OBJS}

Advance.o: Advance.h
Node.o: Node.h Advance.h 

Forest.o: Forest.h Node.h Advance.h

clean:
	rm -f ${OBJS} *.o

memcheck: main
	valgrind --leak-check=full --show-leak-kinds=all ./main
