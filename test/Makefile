SRC_FILES := test.c
EXE_FILES := test
CC := gcc
CC_FLAGS := -Wall -g
LD_FLAGS := -lcunit

.PHONY: all clean

all: test

test: $(SRC_FILES)
	$(CC) -o test $(CC_FLAGS) $(SRC_FILES) ../libclist.a $(LD_FLAGS)

clean:
	rm -rf $(EXE_FILES)
