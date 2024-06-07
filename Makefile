CC = gcc
CFLAGS = -Iinclude
DEPS = include/functions.h
OBJ = src/main.o src/welcome.o src/getLocation.o src/splitArgument.o src/logout.o src/cd.o src/cp.o src/delete.o src/mypipe.o src/move.o src/echoppend.o src/echorite.o src/read.o src/wordCount.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f src/*.o main
