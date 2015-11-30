OBJS = main.o utils.o

CFLAGS =
LDFLAGS =

LIBS =		-lpthread -lncurses

TARGET =	ttytanks

$(TARGET):	$(OBJS)
	$(CC)  $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(TARGET)

all:	$(TARGET)

clean:
	rm $(OBJS) 
	
