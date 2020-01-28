CC = gcc
CFLAGS = -Wall -Werror -g
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXE = test_poly perf_poly

all: $(EXE)

#GCC_OPT= -Wall

%.o: %.c
	$(CC) $(CFLAGS) -c $^

perf_poly: perf_poly.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

test_poly: test_poly.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

perf_poly.o: poly.h
test_poly.o: poly.h
poly.o: poly.h

.PHONY : clean

clean:
	rm -f $(EXE) $(OBJ)
