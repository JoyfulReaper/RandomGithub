CC = g++
CFLAGS = --std=c++11 -c -O0 -ggdb -Wall -Wextra

all: test1 randomGithub

randomGithub: randomGithub.o main.o
	$(CC) randomGithub.o main.o -lcurl -o randomGithub

randomGithub.o: randomGithub.cxx randomGithub.hpp
	$(CC) $(CFLAGS) randomGithub.cxx
	
main.o: main.cpp
	$(CC) $(CFLAGS) -ggdb main.cpp
	
test1: test1.o
	$(CC) test1.o -lcurl -o test1

test1.o: test1.cpp
	$(CC) -c test1.cpp

clean:
	rm -rf *.o test1 randomGithub
