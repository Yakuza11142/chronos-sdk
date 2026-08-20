CC = gcc
CFLAGS = -Wall -Wextra -O3 -std=c11 -I. -Isrc
SRC = src/main.c src/lexer.c src/parser.c src/codegen.c src/disasm.c src/cleanup.c src/vm.c
OBJ = $(SRC:.c=.o)
TARGET = chronos

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
