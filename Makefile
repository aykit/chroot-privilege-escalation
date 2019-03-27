CC = gcc
CFLAGS = -Os -Wall

.PHONY: all
all: build/escalate build/run.so

build/escalate: escalate.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $<

build/run.o: run.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -fpic -o $@ $<

build/run.so: build/run.o
	$(CC) -shared -o $@ $^

.PHONY: clean
clean:
	rm -rf build
