CC = gcc
CFLAGS = -Wall -Werror -g
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXE = test_poly perf_poly test_egalite_poly \
test_addition_poly test_multiplication_scalaire test_eval_poly \
test_multiplication_poly test_puissance_poly test_composition_poly

all: $(EXE)

#GCC_OPT= -Wall

%.o: %.c
	$(CC) $(CFLAGS) -c $^

perf_poly: perf_poly.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

test_poly: test_poly.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

test_egalite_poly : test_egalite_poly.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

test_addition_poly : test_addition_poly.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

test_multiplication_scalaire : test_multiplication_scalaire.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

test_eval_poly : test_eval_poly.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

test_multiplication_poly : test_multiplication_poly.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

test_puissance_poly : test_puissance_poly.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

test_composition_poly : test_composition_poly.o poly.o
	$(CC) $(CFLAGS) -o $@ $^

perf_poly.o: poly.h
test_poly.o: poly.h
test_egalite_poly.o : poly.h
test_addition_poly.o : poly.h
test_eval_poly.o : poly.h
test_multiplication_poly.o : poly.h
test_multiplication_scalaire.o : poly.h
test_puissance_poly.o : poly.h
test_composition_poly.o : poly.h
poly.o: poly.h

.PHONY : clean

clean:
	rm -f $(EXE) $(OBJ)
