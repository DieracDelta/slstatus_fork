# slstatus version
VERSION = 0

# customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib


# flags
CPPFLAGS = -I$(X11INC) -D_DEFAULT_SOURCE
CFLAGS   = -std=c99 -pedantic -Wall -Wextra -Os
LDFLAGS  = -L$(X11LIB) -s
LDLIBS   = -lX11

ifeq ($(ALIENFX), 1)
LDLIBS += -lalienfx
# probably only just need ldflags tbh
CFLAGS += `pkg-config --libs --cflags libusb-1.0`
LDFLAGS += `pkg-config --libs --cflags libusb-1.0`
endif

# compiler and linker
CC = cc
