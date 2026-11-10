CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pedantic -g
TARGET = a.out

SRCS = main.c editor.c cursor.c display.c text.c history.c file.c
OBJS = $(SRCS:.c=.o)
DEPS = editor.h

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) a.out

.PHONY: all run clean
