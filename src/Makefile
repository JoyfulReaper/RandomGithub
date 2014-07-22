$(CC)=g++

all: test1

test1: test1.o
	g++ test1.o -lcurl -o test1

test1.o: test1.cpp
	g++ -c test1.cpp

clean:
	rm -rf *.o test1
