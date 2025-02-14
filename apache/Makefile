CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = 

SRC = getopt_long.c apache.c
OBJ = $(SRC:.c=.o)
TARGET = apache
PREFIX = /usr/local

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c getopt_long.h
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin/
	chmod +x $(PREFIX)/bin/$(TARGET)
	echo "Installed $(TARGET) to $(PREFIX)/bin"

uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)
	echo "Uninstalled $(TARGET)"

clean:
	rm -f $(OBJ) $(TARGET)
	echo "Cleaned up build files"

.PHONY: all install uninstall clean

