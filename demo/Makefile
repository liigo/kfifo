# CC = cc
CFLAGS = -std=c11 -Wall
LDFLAGS = -pthread

target = ./main

build: main.o ../kfifo.o
	${CC} -o ${target} ${LDFLAGS} $^

run: build
	${target}

clean:
	# rm -rf *.o
	find . -name "*.o" | xargs rm -f
	rm -f ${target}

all: clean build

.PHONY: all build clean run
