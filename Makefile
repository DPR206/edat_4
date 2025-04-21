##############################################################
include Makefile_ext
##############################################################
CC = gcc
CFLAGS = -g -Wall
EJS = p4_e1 p4_e2 p4_e3
LDFLAGS = -L.
LDLIBS = -lqueue
##############################################################
OBJECTSP4E1 = p4_e1.o bstree.o vertex.o
OBJECTSP4E2 = p4_e2.o
OBJECTSP4E3 = p4_e3.o
##############################################################

all: $(EJS) clear

p4_e1: $(OBJECTSP4E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4E1) $(LDFLAGS) $(LDLIBS)

p4_e2: $(OBJECTSP4E2)
	$(CC) $(CFLAGS) -o p4_e2 $(OBJECTSP4E2)

p4_e3: $(OBJECTSP4E3)
	$(CC) $(CFLAGS) -o p4_e3 $(OBJECTSP4E3)

p4_e1.o: p4_e1.c
	$(CC) $(CFLAGS) -c p4_e1.c

p4_e2.o: p4_e2.c
	$(CC) $(CFLAGS) -c p4_e2.c

p4_e3.o: p4_e3.c
	$(CC) $(CFLAGS) -c p4_e3.c

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

bstree.o: bstree.c bstree.h
	$(CC) $(CFLAGS) -c bstree.c

file_utils.o: file_utils.c
	$(CC) $(CFLAGS) -c file_utils.c

clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>>>>>Running p4_e1"
	run_e1
	@echo ">>>>>>>>>>Running p4_e2"
	run_e2
	@echo ">>>>>>>>>>Running p4_e3"
	run_e3
runv:
	@echo "Running p4_e1 with valgrind"
	valgrind --leak-check=full --track-origins=yes run_e1
	@echo "Running p4_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes run_e2
	@echo "Running p4_e3 with valgrind"
	valgrind --leak-check=full --track-origins=yes run_e3
