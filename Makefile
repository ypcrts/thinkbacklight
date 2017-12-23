PREFIX := /usr/local

#CC:=clang

# PACKAGES := glib-2.0
# CFLAGS  += $(shell pkg-config --cflags $(PACKAGES))
# LDFLAGS += $(shell pkg-config --libs $(PACKAGES))

CPPFLAGS += -D_DEFAULT_SOURCE

CFLAGS  += -Wall -Wextra -pedantic -Wstrict-overflow -Wno-missing-field-initializers
CFLAGS  += -std=c11 -O3 -fno-strict-aliasing
CFLAGS  += -Wno-unused-variable -Wno-unused-parameter


thinkbacklight: thinkbacklight.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: debug
debug: CFLAGS+=-ggdb3
debug: thinkbacklight

.PHONY: format
format:
	clang-format-4.0 -i -style=google thinkbacklight.c thinkbacklight.h

.PHONY: clean
clean:
	rm -f thinkbacklight

.PHONY: install
install: thinkbacklight
	chown root:root thinkbacklight
	install -D -s -m7755 -t $(PREFIX)/bin thinkbacklight

.PHONY: uninstall
uninstall:
	rm -rf $(PREFIX)/bin/thinkbacklight
