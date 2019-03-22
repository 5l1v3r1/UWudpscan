CFLAGS  = -W -Wall -ansi -I /usr/local/include
CC = cc

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

OBJ = UWudpscan.o send.o res.o recv.o resolv.o

all: $(OBJ)
	$(CC) $(OBJ) -o UWudpscan -lpthread -Wall 
clean:
	rm -f *.o UWudpscan
