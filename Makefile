CFLAGS= -g -std=c99 -Wall -pedantic -D_XOPEN_SOURCE=700 -fsanitize=address

## Working env
BIN_DIR=bin
SRC_DIR=src
DOC_DIR=doc

# Build vars
TARGET=$(BIN_DIR)/main
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(subst $(SRC_DIR),$(BIN_DIR),$(SRC:.c=.o))
# Juste in case ...
CC=gcc

all: $(TARGET)

## Compile main Target
# obj file are in bin not in src so $^ => $(^:src%.o=bin%.o)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

## Compile objects
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@


.PHONY: pack doc clean clean_doc clean_bin

# Build gzip compressed archive
pack: clean
	@cd ../ && tar -czf `basename $(CURDIR)`.tgz `basename $(CURDIR)`/

doc:
	@doxygen

clean: clean_bin clean_doc

clean_doc:
	@rm -rf $(DOC_DIR)/*

# Clean *~ *.o
clean_bin:
	@rm -rf $(BIN_DIR)/*