.PHONY: depend clean   

MAIN=sim-virtual
CC = gcc
CFLAGS= -g -Wall
INCLUDES = -I.

SRCS = memoria.c  main.c lista.c

OBJS = $(SRCS:.c=.o)

$(MAIN):  $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(MAIN) 

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

all: $(MAIN), clean

depend: $(SRCS)
	makedepend $(INCLUDES) $^

clean:
	@rm -f *.o 
	
run:
	@./SCCopy

