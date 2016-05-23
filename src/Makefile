
CC = g++
CFLAGS = -O2 -Wextra -Wall -std=c++11

.PHONY: all clean

all: main

main: vocabulary.o fileparser.o filelistparser.o model.o
	$(CC) $(CFLAGS) $@.cpp -o $@

vocabulary.o: vocabulary.h
	$(CC) $(CFLAGS) -c $< -o $@ 

fileparser.o: fileparser.h
	$(CC) $(CFLAGS) -c $< -o $@ 

filelistparser.o: filelistparser.h
	$(CC) $(CFLAGS) -c $< -o $@ 

model.o: model.h
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf *.o main
