# Dynamic window manager
# See LICENSE file for copyright and license details.

# Version
VERSION = 6.2

# X
X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib
XINERAMALIBS  = -lXinerama
XINERAMAFLAGS = -DXINERAMA

# Freetype
FREETYPELIBS = -lfontconfig -lXft
FREETYPEINC = /usr/include/freetype2

# Libraries
INCS = -I$(X11INC) -I$(FREETYPEINC)
LIBS = -L$(X11LIB) -lX11 $(XINERAMALIBS) $(FREETYPELIBS)

# Flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\" $(XINERAMAFLAGS)
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os $(INCS) $(CPPFLAGS)
LDFLAGS  = $(LIBS)

# Compiler and linker
CC = cc

%.o: src/%.c
	@$(CC) -c $(CFLAGS) $< -o $@

dwm: dwm.o drw.o util.o
	@$(CC) -o $@ *.o $(LDFLAGS)
	@rm *.o
