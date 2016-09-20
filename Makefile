CC:=clang

# CFLAGS+= $(shell pkg-config --cflags $(PACKAGES))
# LDFLAGS+= $(shell pkg-config --libs $(PACKAGES))

CPPFLAGS := -D_DEFAULT_SOURCE


CFLAGS  := -Wall -Wextra -pedantic -Wstrict-overflow 
CFLAGS  += -std=c11 -O2 -fno-strict-aliasing -Wno-missing-field-initalizers
CFLAGS  += -march=native

LDFLAGS := 

thinkbacklight: thinkbacklight.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: format
format:
	clang-format-4.0 -i -style=llvm thinkbacklight.c thinkbacklight.h
