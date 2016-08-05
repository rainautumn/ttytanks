#clang also works good
CC = gcc
SRCS = main.c utils.c kernel.c
CFLAGS = -std=c11 -O2 -march=native -pipe
LDLIBS = -lpthread -lncurses -lm
TARGET = ttytanks
#static binary by default, should be faster than dynamicaly linked
static:
	$(CC)  $(SRCS) $(LDLIBS) $(CFLAGS) -static -o $(TARGET)
dynamic:
	$(CC) $(SRCS) $(LDLIBS) $(CFLAGS) -o $(TARGET)
clean:
	rm $(TARGET)
