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
LIGHTSRCS =  lightsources/main.c \
             lightsources/core.c \
             lightsources/multiplayer.c \
             lightsources/canvas.c  \
             lightsources/render.c
# lightsources compilled without any errors, source code pretty simple, so lightsources by default^

MAINSRCS = sources/main.c \
           sources/core.c \
           sources/multiplayer.c\
           sources/canvas.c \
           sources/render.c
#main sources, gamespace in center of terminal, a lot of warnings while compiling^

SRCS = $(LIGHTSRCS) #Lightsources by default

OBJS = objects/main.o \
       objects/core.o \
       objects/multiplayer.o \
       objects/canvas.o \
       objects/render.o #for checking for objects

# Warnings, ttytanks with -std=c11 can't be compilled with -Werror, -pedantic-errors, you should add this flags in future,
# now just comment it if you use sources/*.c
WCFLAGS = -Wall -Wextra -pedantic -Werror=pedantic -Wfatal-errors -pedantic-errors -Werror -v

PLOOPS = -ftree-parallelize-loops=4 # loop optimization for N cores, comment it when make precompilled binaries

MARCH = -march=native # CPU architecture, comment when make precompilled binaries

#Optimizations for debugging, use gdb (GNU Debugger) with compiled binary
#To install gdb install it first.
# emerge -av sys-devel/gdb
# Use ulimit -c to check whether .core dumps are allowed, if size is 0, change it, ulimut -c unlimited, .core dump files produced if program is crashed
# -pg for GNU profiler
ODEBUG = -Og \
         -pg \
         -fprofile-report \
         -fprofile-arcs \
         -ftest-coverage   # count how often different branches of conditionals executed
#-gstabs+ -gstabs -g3 -ggdb -gdwarf-5 #options for debugging with GDB, not used yet.


# How to Use GDB:
# gdb <executable file> <core file>

# For analysis performance use grof (GNU Profiler), it shows how often each function is used.
# gprof <executable>
# with statically linked binary gprof also shows usage of external functions (printf,mvaddstr)


#Optimizations for gaming
OGAME = -Ofast $(PLOOPS) -funroll-loops

#Optimize for debugging by default, use it with dynamicaly linked binary, you can read also some info in .o files with 'less' and in binary itself, it's do 4n't require debugging flags.
OPTMZ = $(ODEBUG)

# -std=c11 not works good, look for warning with clang
# -Ofast -funroll-loops safe options for this game, for debugging use -Og
CFLAGS = $(WCFLAGS) -std=gnu11 $(OPTMZ) $(MARCH) -pipe
# you may need -ltinfo in LDLIBS
LDLIBS = -lpthread -lncurses -lm #-ltinfo
TARGET = ttytanks

# make precompiled script
#PRECOMPILED = ./makeprecompiled

# static binary by default, faster than dynamicaly linked, more portable if disable -march=native, you can use it on systems
# such as embedded systems, android smartphones, so on...
default:
	make --trace --debug=v static

#Make staticaly linked (standalone) binary, -j option not works for making statically linked binary
static: $(SRCS)
	$(CC)   $(SRCS) $(LDLIBS) $(CFLAGS) -static -o static_$(TARGET)
dynamic: $(SRCS)
	make -j4 objects # Make with 4 threads, max value 5
	make target

# Not works yet, I don't know how to call external script, or loop in Makefile, so use standalone script makeprecompiled
#precompiled: $(SRCS) # Make precompiled binaries, only static, only from lightsources, so it must be very portable;
#	$(PRECOMPILED) $(CC) $(SRCS) $(LDLIBS) $(CFLAGS)

#Make dynamicaly linked binary. You can't use -j option for static or dynamic, only for objects

# render, canvas, multiplayer, core. main, objects, target - options for developing
# Make objects, useful for developing:
render: $(SRCS)
	$(CC) -c lightsources/render.c $(CFLAGS) -o objects/render.o
canvas: $(SRCS)
	$(CC) -c lightsources/canvas.c $(CFLAGS) -o objects/canvas.o
multiplayer: $(SRCS)
	$(CC) -c lightsources/multiplayer.c $(CFLAGS) -o objects/multiplayer.o
core: $(SRCS)
	$(CC) -c lightsources/core.c $(CFLAGS) -o objects/core.o
main: $(SRCS)
	$(CC) -c lightsources/main.c $(CFLAGS) -o objects/main.o
objects: render canvas multiplayer core main #Use 'make -jN objects' for making objects, where is N number of threads at last 5;
                                             # 'make -jN objects' works 2 time faster than 'make dynamic'
#link objects into single dynamically linked binary
target: $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) $(CFLAGS) -o dynamic_$(TARGET)
statistics:
	gprof *_$(TARGET) > statistics/functions

#Make all types for comparing
all: static dynamic

install: *_$(TARGET)
	mv -uv *_$(TARGET) /usr/bin/$(TARGET)
uninstall:
	rm -v /usr/bin/$(TARGET)
clean:
	rm *_$(TARGET) objects/* gmon.out statistics/*
