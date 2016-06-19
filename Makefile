CC = gcc -std=c11
OBJS = main.o utils.o kernel.o

LIBS =		-lpthread -lncurses

TARGET =	ttytanks

$(TARGET):	$(OBJS)
	$(CXX)  $(OBJS) $(LIBS) -o $(TARGET)

all:	$(TARGET)

clean:
	rm $(OBJS) 
