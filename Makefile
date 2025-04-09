CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude
LIBS = -lsqlite3

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = orangerie_app

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
