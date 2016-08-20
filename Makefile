# Makefile for ttytanks
#
# Created on:   2016/08/19
# Author:       DmitryHetman
# Contributors:

# You should use gprof for detecting most frequently used functions and lines of code and optimize it
# Read "An Introduction to GCC" p.75
# Read man gcc Debuging options
# Use also GNU debugger for removing bugs.
# Also may be useful link executable with -lncurses_g debuging library

# clang also works good, clang with -O0 should be better for removing warnings
# clang compile slower than gcc, but provide good output
CC = gcc
# multiplayer disabled yet, you can add it for testing purposes, or for finish it, add it after core.c
LIGHTSRCS =  lightsources/main.c lightsources/core.c lightsources/multiplayer.c lightsources/canvas.c lightsources/render.c
# lightsources compilled without any errors, source code pretty simple, so lightsources by default^

MAINSRCS = sources/main.c sources/core.c sources/canvas.c sources/render.c
#main sources, gamespace in center of terminal, a lot of warnings while compiling^

SRCS = $(LIGHTSRCS) #Lightsources by default

OBJS = main.o core.o multiplayer.o canvas.o render.o #for checking for objects

# Warnings, ttytanks with -std=c11 can't be compilled with -Werror, -pedantic-errors, you should add this flags in future,
# now just comment it if you use sources/*.c
WCFLAGS = -Wall -Wextra -pedantic -Werror=pedantic -Wfatal-errors -pedantic-errors -Werror -v

PLOOPS = -ftree-parallelize-loops=4 # loop optimization for N cores, comment it when make precompilled binaries

MARCH = -march=native # CPU architecture, comment when make precompilled binaries

# -std=c11 not works good, look for warning with clang
# -Ofast -funroll-loops safe options for this game, for debugging use -Og
CFLAGS = $(WCFLAGS) -std=gnu11 -Ofast -pipe $(PLOOPS) -funroll-loops $(MARCH)
# you may need -ltinfo in LDLIBS
LDLIBS = -lpthread -lncurses -lm #-ltinfo
TARGET = ttytanks

# make precompiled script
PRECOMPILED = ./makeprecompiled

# static binary by default, faster than dynamicaly linked, more portable if disable -march=native, you can use it on systems
# such as embedded systems, android smartphones, so on...
default: static

#Make staticaly linked (standalone) binary, -j option not works for making statically linked binary
static: $(SRCS)
	$(CC)  $(SRCS) $(LDLIBS) $(CFLAGS) -static -o static_$(TARGET)
dynamic: $(SRCS)
	make -j4 objects # Make with 4 threads, max value 5
	make target

# Not works yet, I don't know how to call external script, or loop in Makefile, so use standalone script makeprecompiled
precompiled: $(SRCS) # Make precompiled binaries, only static, only from lightsources, so it must be very portable;
	$(PRECOMPILED) $(CC) $(SRCS) $(LDLIBS) $(CFLAGS)

#Make dynamicaly linked binary. You can't use -j option for static or dynamic, only for objects

# render, canvas, multiplayer, core. main, objects, target - options for developing
# Make objects, useful for developing:
render: $(SRCS)
	$(CC) -c lightsources/render.c $(CFLAGS)
canvas: $(SRCS)
	$(CC) -c lightsources/canvas.c $(CFLAGS)
multiplayer: $(SRCS)
	$(CC) -c lightsources/multiplayer.c $(CFLAGS)
core: $(SRCS)
	$(CC) -c lightsources/core.c $(CFLAGS)
main: $(SRCS)
	$(CC) -c lightsources/main.c $(CFLAGS)
objects: render canvas multiplayer core main #Use 'make -jN objects' for making objects, where is N number of threads at last 5;
                                             # 'make -jN objects' works 2 time faster than 'make dynamic'
#link objects into single dynamically linked binary
target: $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o dynamic_$(TARGET)

#Make all types for comparing
all: static dynamic

install: *$(TARGET)
	mv -uv *$(TARGET) /usr/bin/$(TARGET)
uninstall:
	rm -v /usr/bin/$(TARGET)
clean:
	rm *$(TARGET) *.o
