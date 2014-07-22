CC = g++

all: test1 randomGithub

randomGithub: randomGithub.o main.o
	$(CC) randomGithub.o main.o -lcurl -o randomGithub

randomGithub.o: randomGithub.cxx randomGithub.hpp
	$(CC) -c -O0 -ggdb randomGithub.cxx
	
main.o: main.cpp
	$(CC) -c -O0 -ggdb main.cpp
	
test1: test1.o
	$(CC) test1.o -lcurl -o test1

test1.o: test1.cpp
	$(CC) -c test1.cpp

clean:
	rm -rf *.o test1 randomGithub
