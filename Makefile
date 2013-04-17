# This makefile should handle all things.

# Detect OS.
OS := $(shell uname -s)

ifeq ($(OS),Darwin) # OS X

ifeq ($(CC),)
CC := xcrun clang
endif

ifeq ($(LD),)
LD := $(CC)
endif

CFLAGS += -arch i386 -arch x86_64
LDFLAGS += -arch i386 -arch x86_64

SO := dylib

else

ifeq ($(CC),)
CC := gcc
endif

ifeq ($(LD),ld)
LD := $(CC)
endif

SO := so

endif

CFLAGS += -std=c99 -fPIC

PREFIX := /usr/local
TARGET := libdebug.$(SO)
OBJS := debug.o

all: $(TARGET)
.PHONY: all clean install uninstall

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -shared $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm $(TARGET)
	-rm $(OBJS)

install: all
	cp $(TARGET) $(PREFIX)/lib
	cp $(OBJS:.o=.h) $(PREFIX)/include

uninstall:
	-rm $(PREFIX)/lib/$(TARGET)
	-cd $(PREFIX)/include && rm $(OBJS:.o=.h)
