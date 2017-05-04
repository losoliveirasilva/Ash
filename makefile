TARGET = Ash
CFLAGS = -std=c11 -Wall -Wextra -Werror -pedantic -O

all: $(TARGET)

debug: CFLAGS += -g
debug: $(TARGET)

run: $(TARGET)
	@./$(TARGET)
