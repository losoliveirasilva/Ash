CFLAGS = -std=c11 -Wall -Wextra -Werror

all: Ash

Ash: Ash.c
	$(CC) $(CFLAGS) $^ -o $@
