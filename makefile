FLAGS = -g -Wall -pedantic -c
CC = gcc

p2_e1a: p2_e1a.o point.o map.o
	$(CC) -g -o p2_e1a p2_e1a.o point.o map.o -lm

p2_e1a.o: p2_e1a.c point.h map.h
	$(CC) $(FLAGS) p2_e1a.c

map.o: map.c map.h point.h types.h
	$(CC) $(FLAGS) map.c

point.o: point.c point.h types.h
	$(CC) $(FLAGS) point.c

clean:
	rm *.o

cleanall:
	rm *.o
	rm p2_e1a