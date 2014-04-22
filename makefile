CC=clang
CFLAGS=-g -Weverything -O2

hanoi:
	$(CC) $(CFLAGS) -o hanoi hanoi.c
