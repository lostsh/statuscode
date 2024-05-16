CFLAGS= -g -std=c99 -Wall -pedantic -D_XOPEN_SOURCE=700 -fsanitize=address

## Working env
BIN_DIR=bin/
SRC_DIR=src/
DOC_DIR=doc/

# Build vars
TARGET=$(BIN_DIR)/main
SRC=$(wildcard $(SRC_DIR)/*.go)

CC=go build

all: $(TARGET)

## Compile main Target
# obj file are in bin not in src so $^ => $(^:src%.o=bin%.o)
$(TARGET): $(SRC)
	$(CC) -o $@ $^

.PHONY: doc clean clean_doc clean_bin

doc:
	@doxygen

clean: clean_bin clean_doc

clean_doc:
	@rm -rf $(DOC_DIR)/*

# Clean *~ *.o
clean_bin:
	@rm -rf $(BIN_DIR)/*


go build -o bin/ src/main.go
