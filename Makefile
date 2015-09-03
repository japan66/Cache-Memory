CC = gcc
CFLAGS = -g -Wall
FILE = cache_simulator.c

all: cache_sim

cache_sim: cache_simulator.c cache_simulator.h
	$(CC) $(CFLAGS) $(FILE) -o cache_simulator

clean:
	rm -rf *.o
	rm -f cache_simulator
	rm -rf *.dSYM # on MacOSX
