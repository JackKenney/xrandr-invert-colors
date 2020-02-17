.POSIX:

CFLAGS = -Wall -Wextra -O0 -ggdb -std=c99
LIBS   = -lxcb-randr -lxcb -lm

PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
TARGET = xrandr-invert-colors

SRC = gamma_randr.c hsv_conversion.c invert_gamma_ramps.c xrandr-invert-colors.c 
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

$(OBJ): gamma_randr.h hsv_conversion.h invert_gamma_ramps.h

clean:
	rm -f $(TARGET) $(OBJ)

install: $(TARGET)
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(TARGET) $(DESTDIR)$(BINDIR)
	chmod 755 $(DESTDIR)$(BINDIR)/$(TARGET)
	#chown root:root $(DESTDIR)$(BINDIR)/$(TARGET) # not needed if make run as root

deps-apt:
	apt-get install libxcb-randr0-dev

