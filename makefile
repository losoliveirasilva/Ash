CFLAGS = -std=c11 -Wall -Wextra -Werror -g

all: Ash

Ash: Ash.c
	$(CC) $(CFLAGS) $^ -o $@
