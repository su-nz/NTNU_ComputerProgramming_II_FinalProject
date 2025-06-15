CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function
CFLAGS += -Iexternal/SDL/include -Iexternal/SDL_mixer/include

SRC = TwistedFables.c Function.c Skill.c Card.c vector.c board_gui.c
OBJ = $(SRC:.c=.o)
TARGET = TwistedFables

LIBS = \
  raylib/build/raylib/libraylib.a \
  external/SDL/build/libSDL2.a \
  external/SDL_mixer/build/libSDL2_mixer.a \
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
