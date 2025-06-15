CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function
CFLAGS += -Iinclude

SRC = TwistedFables.c Function.c Skill.c Card.c vector.c board_gui.c
OBJ = $(SRC:.c=.o)
TARGET = TwistedFables

LIBS = \
  ./libraylib.a \
  ./libSDL2.a \
  ./libSDL2_mixer.a \
  -lGL -lm -lpthread -ldl -lrt -lX11

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)
