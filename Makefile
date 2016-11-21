SNAME   := libclist.a
DNAME   := libclist.so
SRC     :=  $(wildcard src/*.c)

SDIR    :=  build-static
SOBJ    :=  $(SRC:src/%.c=$(SDIR)/%.o)

DDIR    :=  build-shared
DOBJ    :=  $(SRC:src/%.c=$(DDIR)/%.o)

CFLAGS  :=   -Wall -Wextra -Werror -Iinclude

.PHONY: all clean install lib_static lib_shared

all: lib_static lib_shared

lib_static: $(SNAME)
lib_shared: $(DNAME)

$(SNAME): $(SOBJ)
	$(AR) $(ARFLAGS) $@ $^

$(DNAME): CFLAGS += -fPIC
$(DNAME): $(DOBJ)
	$(CC) -shared -Wl,-soname,libclist.so.1.0.0 $^ -o $@

$(SDIR)/%.o: src/%.c | $(SDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(DDIR)/%.o: src/%.c | $(DDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

$(SDIR) $(DDIR):
	@mkdir $@

clean:
	$(RM) -r $(SDIR) $(DDIR) $(SNAME) $(DNAME)

install: all
	$(info install files)
	@mkdir --parents /usr/local/include/libclist
	@install -m 0644 include/*.h /usr/local/include/libclist
	@install libclist.so /usr/local/lib
	@install libclist.a /usr/local/lib
	ldconfig