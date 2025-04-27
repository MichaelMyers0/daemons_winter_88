CC=cc
CCFLAGS=-Wall -Wextra
find.o:find.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
stack.o:stack.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
daemon.o:daemon.c
	$(CC) $(CCFLAGS) -g -c -O $< -o $@
main:main.c daemon.o stack.o find.o
	$(CC) $(CCFLAGS) -g -O $^ -o $@

