CFLAGS=-c -Wall -O2
LIBS = -loled96 -lm -lpthread

all: ipscreen

ipscreen: ipscreen.o
	$(CC) ipscreen.o $(LIBS) -o ipscreen

ipscreen.o: ipscreen.c
	$(CC) $(CFLAGS) ipscreen.c

clean:
	rm -rf *.o ipscreen
