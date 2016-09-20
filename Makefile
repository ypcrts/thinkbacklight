CC:=clang

PACKAGES := glib-2.0

CFLAGS  += $(shell pkg-config --cflags $(PACKAGES))
LDFLAGS += $(shell pkg-config --libs $(PACKAGES))

CPPFLAGS += -D_DEFAULT_SOURCE

CFLAGS  += -Wall -Wextra -pedantic -Wstrict-overflow -Wno-missing-field-initalizers
CFLAGS  += -std=c11 -O2 -fno-strict-aliasing
CFLAGS  += -march=native


thinkbacklight: thinkbacklight.c format
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: format
format:
	clang-format-4.0 -i -style=google thinkbacklight.c thinkbacklight.h
