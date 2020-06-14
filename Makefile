all: stack

grid: stack.c
	$(CC) stack.c -o stack -Wall -g -Wextra -pedantic -std=c99 -lm
