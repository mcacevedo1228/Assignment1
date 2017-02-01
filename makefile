CC = gcc
CFLAGS = -O4 -Wall -mavx2 -I $(TIMER_DIR)
TIMER_DIR = /Users/marcacevedo/Desktop/Loyola\ University\ Maryland/Spring\ 2017/Computer\ Systems/Assignments/Assignment2
TIMER = $(TIMER_DIR)/clock.o $(TIMER_DIR)/fcycmm.o

all: mm 

mm: mm.c mm.h
	$(CC) $(CFLAGS) -o mm mm.c $(TIMER)

clean:
	rm -f *.o mm *~

print:
	a2ps -L70 --delegate=no -T 4 -q -Avirtual -2 -o xd mm.h mm.c 





