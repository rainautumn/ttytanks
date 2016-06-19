CC = gcc 
OBJS = main.o utils.o kernel.o
CFLAGS = -std=c11 -02 -march=native -pipe
LIBS =		-lpthread -lncurses

TARGET =	ttytanks

$(TARGET):	$(OBJS)
	$(CC)  $(OBJS) $(LIBS) $(CFLAGS) -o $(TARGET)

all:	$(TARGET)

clean:
	rm $(OBJS) 
