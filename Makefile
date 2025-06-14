CC = gcc
CFLAGS =  --std=c99

SRC = TwistedFables.c Function.c Skill.c Card.c vector.c
OBJ = $(SRC:.c=.o)
TARGET = TwistedFables

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
