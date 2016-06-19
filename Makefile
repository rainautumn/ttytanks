CC = gcc
OBJS = main.o utils.o kernel.o
CFLAGS = -std=c11 -O2 -march=native -pipe
LDLIBS = -lpthread -lncurses -lm -ltinfo
TARGET = ttytanks
$(TARGET): $(OBJS)
        $(CC)  $(OBJS) $(CFLAGS) $(LDLIBS) -o $(TARGET)
all:    $(TARGET)
clean:
        rm $(TARGET) $(OBJS}
