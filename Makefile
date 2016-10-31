CC = clang++
CFLAGS  = -g -Wall -std=c++1z

main:	main.o shell_listener.o
	$(CC) $(CFLAGS) -o main main.o shell_listener.o -pthread -lutil

main.o:	main.cpp shell_listener.h
	$(CC) $(CFLAGS) -c main.cpp

shell_listener.o:	shell_listener.cpp shell_listener.h
	$(CC) $(CFLAGS) -c shell_listener.cpp

clean:
	$(RM) main *.c *~