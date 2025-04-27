CC=cc
CCFLAGS=-Wall -Wextra
daemon.o:daemon.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
main:main.c daemon.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@

