CC=gcc
CFLAGS=-Wall

all: $(patsubst %.c,%,$(wildcard *.c))

%: %.c
	$(CC) $(CFLAGS) -o $@ $<
