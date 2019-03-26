CC = gcc
CFLAGS = -Os -Wall

.PHONY: all
all: build/escalate build/run.so

build:
	mkdir build

build/escalate: escalate.c build
	$(CC) $(CFLAGS) -o $@ $<

build/run.o: run.c build
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

build/run.so: build/run.o
	$(CC) -shared -o $@ $^

.PHONY: clean
clean:
	rm -rf build
