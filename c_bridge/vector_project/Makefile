CC = gcc

CFLAGS = -std=c11 -Wall -Wpedantic -Wextra -g

SAN = -fsanitize=address,undefined

TARGET = vector_app

all: $(TARGET)

$(TARGET): vector.h vector.c main.c 
	$(CC) $(CFLAGS) $(SAN) vector.c main.c -o $(TARGET)

clean:
	rm -f $(TARGET)