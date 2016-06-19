OBJS = main.o utils.o kernel.o
CFLAGS = -std=c99 -march=native -02 -pipe
LDFLAGS =

LIBS = -lpthread -lncurses

TARGET = ttytanks

$(TARGET):	$(OBJS)
	gcc  $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(TARGET)

all:	$(TARGET)

clean:
	rm $(OBJS)
