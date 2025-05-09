##############################################################
CC = gcc
CFLAGS = -g -Wall
EJS = p4_e1 p4_e2 p4_e3
##############################################################
OBJECTSP4E1 = p4_e1.o bstree.o vertex.o
OBJECTSP4E2 = p4_e2.o bstree.o search_queue.o file_utils.o
OBJECTSP4E3 = p4_e3.o bstree.o search_queue.o file_utils.o
##############################################################

all: $(EJS) clear

p4_e1: $(OBJECTSP4E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4E1)

p4_e2: $(OBJECTSP4E2)
	$(CC) $(CFLAGS) -o p4_e2 $(OBJECTSP4E2)

p4_e3: $(OBJECTSP4E3)
	$(CC) $(CFLAGS) -o p4_e3 $(OBJECTSP4E3)

p4_e1.o: p4_e1.c bstree.h vertex.h types.h
	$(CC) $(CFLAGS) -c p4_e1.c

p4_e2.o: p4_e2.c bstree.h search_queue.h file_utils.h types.h
	$(CC) $(CFLAGS) -c p4_e2.c

p4_e3.o: p4_e3.c bstree.h search_queue.h file_utils.h types.h
	$(CC) $(CFLAGS) -c p4_e3.c

vertex.o: vertex.c vertex.h
	$(CC) $(CFLAGS) -c vertex.c

bstree.o: bstree.c bstree.h
	$(CC) $(CFLAGS) -c bstree.c

search_queue.o: search_queue.c search_queue.h bstree.h
	$(CC) $(CFLAGS) -c search_queue.c

file_utils.o: file_utils.c
	$(CC) $(CFLAGS) -c file_utils.c

clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>>>>>Running p4_e1"
	make run_e1
	@echo ">>>>>>>>>>Running p4_e2"
	make run_e2
	@echo ">>>>>>>>>>Running p4_e3"
	make run_e3
runv:
	@echo "Running p4_e1 with valgrind"
	make run_e1 VALGRIND="valgrind --leak-check=full --track-origins=yes"
	@echo "Running p4_e2 with valgrind"
	make run_e2 VALGRIND="valgrind --leak-check=full --track-origins=yes"
	@echo "Running p4_e3 with valgrind"
	make run_e3 VALGRIND="valgrind --leak-check=full --track-origins=yes"

##############################################################
include Makefile_ext