#clang also works good
#you should use gprof for detecting most frequently used functions and lines of code
#Read "An Introduction to GCC" p75
CC = gcc
SRCS = main.c utils.c kernel.c
CFLAGS = -Wall -Wextra -v -std=c11 -Ofast -funroll-loops -march=native -pipe
LDLIBS = -lpthread -lncurses -lm
TARGET = ttytanks
#static binary by default, should be faster than dynamicaly linked
static:
	$(CC)  $(SRCS) $(LDLIBS) $(CFLAGS) -static -o $(TARGET)
dynamic:
	$(CC) $(SRCS) $(LDLIBS) $(CFLAGS) -o $(TARGET)
clean:
	rm $(TARGET)
