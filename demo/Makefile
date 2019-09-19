# CC = cc
CFLAGS = -std=c11 -Wall
LDFLAGS = -lpthread

target = main

build: main.o ../kfifo.o
	${CC} -o ${target} ${LDFLAGS} $^

run: build
	./${target}

clean:
	rm -rf *.o
	rm -f ${target}

all: clean build

.PHONY: all build clean run
