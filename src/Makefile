CC = g++
CFLAGS = --std=c++11 -c -O0 -ggdb -pthread -Wall -Wextra

all: randomGithub gtkRandomGithub

gtkRandomGithub: gtk_main.o mainWindow.o randomGithub.o
	$(CC) randomGithub.o mainWindow.o gtk_main.o `pkg-config gtkmm-3.0 --libs --cflags` -lcurl -o gtkRandomGithub

gtk_main.o: gtk_main.cpp mainWindow.o randomGithub.o
	$(CC) $(CFLAGS) `pkg-config gtkmm-3.0 --cflags` gtk_main.cpp

mainWindow.o: mainWindow.cxx mainWindow.hpp randomGithub.hpp
	$(CC) $(CFLAGS) `pkg-config gtkmm-3.0 --cflags` mainWindow.cxx 

randomGithub: randomGithub.o main.o
	$(CC) randomGithub.o main.o -lcurl -o randomGithub

randomGithub.o: randomGithub.cxx randomGithub.hpp gitRepo.hpp
	$(CC) $(CFLAGS) randomGithub.cxx

main.o: main.cpp randomGithub.hpp
	$(CC) $(CFLAGS) main.cpp
	
test1: test1.o
	$(CC) test1.o -lcurl -o test1

test1.o: test1.cpp
	$(CC) -c test1.cpp

clean:
	rm -rf *.o test1 randomGithub gtkRandomGithub
