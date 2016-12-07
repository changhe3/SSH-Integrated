CC = clang++
CFLAGS  = -g -Wall -std=c++1z 
LDFLAGS = -lrote -lncurses -lmenu -lpanel

all: main

main.o:	main.cpp shell_listener.h
	$(CC) $(CFLAGS) -c main.cpp

shell_listener.o:	shell_listener.cpp shell_listener.h 
	$(CC) $(CFLAGS) -c shell_listener.cpp 

main:	main.o shell_listener.o
	$(CC) $(CFLAGS) -o main main.o shell_listener.o $(LDFLAGS)

clean:
	$(RM) main *.o 