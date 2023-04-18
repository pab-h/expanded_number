CC=gcc
CFLAGS=-I ./headers
BUILD_DIR=./build
SRC_DIR=./src
HEADER_DIR=./headers
EXAMPLE_DIR=./example

_DEPS = stack.h expanded_number.h
DEPS = $(patsubst %,$(HEADER_DIR)/%,$(_DEPS))

_OBJ = stack.o expanded_number.o
OBJ = $(patsubst %,$(BUILD_DIR)/%,$(_OBJ))


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAGS)

factorial: $(OBJ) $(EXAMPLE_DIR)/factorial.c
	$(CC) -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

create: $(OBJ) $(EXAMPLE_DIR)/create.c
	$(CC) -o $(BUILD_DIR)/$@ $^ $(CFLAGS)

run_factorial: factorial
	$(BUILD_DIR)/$^

run_create: create
	$(BUILD_DIR)/$^

clean:
	rm -fr $(BUILD_DIR)