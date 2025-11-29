CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -g
INCLUDE = -Iinclude
SRC     = src/allocator.c src/main.c
OBJ     = $(SRC:.c=.o)
TARGET  = allocator_demo

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
