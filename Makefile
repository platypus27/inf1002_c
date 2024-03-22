CC=gcc
CFLAGS=-I.
DEPS = main.c src/*.c
OBJ = main.o src/*.c

%.o: %.c $(DEPS)
    $(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
    $(CC) -o $@ $^ $(CFLAGS)