CC = gcc
CFLAGS = -g
TARGET = words map limits

all: $(TARGET)

words: word_count.o main.o wc_sort.o
	$(CC) -o words word_count.o main.o wc_sort.o

map: map.o
	$(CC) -o map map.o

limits: limits.o
	$(CC) -o limits limits.o

word_count.o: word_count.c word_count.h
	$(CC) $(CFLAGS) -c word_count.c

limits.o: limits.c
	$(CC) $(CFLAGS) -c limits.c

map.o: map.c
	$(CC) $(CFLAGS) -c map.c

main.o: main.c word_count.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -rf $(filter-out wc_sort.o, $(wildcard *.o)) $(TARGET)
