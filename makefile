CC=cc
CCFLAGS=-Wall -Wextra
main:main.c
	$(CC) $(CCFLAGS) -g $< -o $@

