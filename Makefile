CC = gcc
CFLAGS = -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lSDL2
SOURCES = $(find . -name "*.c")
EXECUTABLE = programa

all: build run

build:
	gcc *.c -o game -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2

run:
	./game
