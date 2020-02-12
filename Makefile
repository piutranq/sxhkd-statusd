CC = gcc

INC = include
CFLAGS = -std=c99 -Wall -Wextra -g -I $(INC)

OBJS = src/main.o src/err.o src/event.o src/init.o src/config.o src/msg.o
SRCS = src/main.c src/err.c src/event.c src/init.c src/config.c src/msg.c

TARGET = sxhkd-statusd

PREFIX ?= /usr/local/bin/

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -rf src/*.o $(TARGET)

install:
	mkdir -p $(PREFIX)
	cp -pf $(TARGET) $(PREFIX)$(TARGET)

uninstall:
	rm -f $(PREFIX)$(TARGET)

