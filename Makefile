CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function

SRC = TwistedFables.c Function.c Skill.c Card.c vector.c board_gui.c
OBJ = $(SRC:.c=.o)
TARGET = TwistedFables

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

