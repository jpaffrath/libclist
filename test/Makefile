SRC_FILES := test.c
EXE_FILES := test
LIB_FILES := $(wildcard ../src/*.c)
CC := gcc
CC_FLAGS := -Wall -g -fprofile-arcs -ftest-coverage -I../include

.PHONY: all clean

all: test

test: $(SRC_FILES)
	$(CC) -o test $(CC_FLAGS) $(SRC_FILES) $(LIB_FILES) -lcunit

clean:
	rm -rf $(EXE_FILES)
