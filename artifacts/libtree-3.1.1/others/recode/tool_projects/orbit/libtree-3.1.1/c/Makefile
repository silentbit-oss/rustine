-include Make.user

CFLAGS ?= -O2
LIBTREE_CFLAGS = -std=c99 -Wall -Wextra -Wshadow -pedantic
LIBTREE_DEFINES = -D_FILE_OFFSET_BITS=64

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
SHAREDIR ?= $(PREFIX)/share

.PHONY: all check install clean coverage

# Build the libtree static object file
# libtree.o: libtree.c libtree.h
# 	$(CC) $(CFLAGS) -c libtree.c -o libtree.o
libtree.o: libtree.c libtree.h
	$(CC) $(CFLAGS) $(LIBTREE_CFLAGS) $(LIBTREE_DEFINES) -c libtree.c -o libtree.o



# Build the main libtree binary (if needed later, you can comment/remove this if not needed)
libtree: libtree.o
	$(CC) $(LDFLAGS) -o $@ $^

# # Build test binary
# tests/test: tests/test.c libtree.o
# 	$(CC) $(CFLAGS) tests/test.c libtree.o -o tests/test
tests/test: tests/test.c libtree.o
	@echo "Compiling with CFLAGS=$(CFLAGS)"
	@echo "Compiling with LDFLAGS=$(LDFLAGS)"
	$(CC) $(CFLAGS) tests/test.c libtree.o -o tests/test $(LDFLAGS)

check: tests/test
	./tests/test


# coverage: clean
# 	$(MAKE) CFLAGS="-O0 -g -fprofile-arcs -ftest-coverage" LDFLAGS="--coverage" check
# 	gcov libtree.c tests/test.c
coverage: clean
	$(MAKE) \
	  CFLAGS="-O0 -g -fprofile-arcs -ftest-coverage" \
	  LDFLAGS="--coverage" \
	  LIBTREE_CFLAGS="" \
	  LIBTREE_DEFINES="" \
	  libtree.o tests/test
	./tests/test
	gcov -o . libtree.c
	gcov -o tests tests/test-test.gcno

install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	cp -p libtree $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(SHAREDIR)/man/man1
	cp -p doc/libtree.1 $(DESTDIR)$(SHAREDIR)/man/man1

clean:
	rm -f *.o *.gcno *.gcda *.gcov libtree
	rm -f tests/test tests/*.o tests/*.gcno tests/*.gcda tests/*.gcov
