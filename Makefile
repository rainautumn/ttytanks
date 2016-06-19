CC = gcc -std=c99
OBJS = main.o utils.o kernel.o

CFLAGS = -march=native -02 -pipe
LDFLAGS =

LIBS =		-lpthread -lncurses

TARGET =	ttytanks

$(TARGET):	$(OBJS)
	g++  $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(TARGET)

all:	$(TARGET)

clean:
	rm $(OBJS) 
	
