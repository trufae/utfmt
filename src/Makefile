CC ?= cc
CFLAGS ?= -std=c99 -Wall -Wextra -O2

utfmt: utfmt.c
	$(CC) $(CFLAGS) -o $@ utfmt.c

test: utfmt
	./utfmt ../text.utfmt

clean:
	rm -f utfmt
