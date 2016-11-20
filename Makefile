SRC_FILES := $(wildcard src/*.c)
OBJ_FILES := $(addprefix obj/,$(notdir $(SRC_FILES:.c=.o)))
LIB_FILES := libclist.so
CC := gcc
CC_FLAGS := -Wall -Wextra -Werror -Iinclude -fPIC -c -o
LD_FLAGS := -shared -Wl,-soname,libclist.so.1.0.0

.PHONY: all test clean install

all: $(LIB_FILES)

obj/%.o: src/%.c
	$(CC) $(CC_FLAGS) $@ $<

libclist.so: $(OBJ_FILES)
	$(info link library)
	@$(CC) $(LD_FLAGS) -o libclist.so $(OBJ_FILES)

test: $(LIB_FILES)
	$(MAKE) -C test

clean:
	@rm -rf $(LIB_FILES) $(OBJ_FILES)

install: all
	$(info install files)
	@mkdir --parents /usr/local/include/libclist
	@install -m 0644 include/*.h /usr/local/include/libclist
	@install libclist.so /usr/local/lib
	ldconfig
