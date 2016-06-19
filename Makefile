CFLAGS = -std=c11
OBJS = main.o utils.o kernel.o

LDLIBS = -lpthread -lncurses -lm -ltinfo

TARGET = ttytanks

$(TARGET): $(OBJS)

all: $(TARGET)

clean:
	rm $(OBJS)

