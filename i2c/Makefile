CC=armv7l-timesys-linux-gnueabi-gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=main
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

main: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

main.o: ensea_i2c.h acc.h

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf *.o

mrproper: clean
		@rm -rf $(EXEC)
