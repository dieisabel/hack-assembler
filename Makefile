SHELL := /usr/bin/env bash

CC            := gcc
STD           := c11
HEADERS       := ./include
CFLAGS        := -Wall --std=$(STD) -g $(foreach header_path, $(HEADERS), -I $(header_path))

DEBUGGER := gdb

SRC := ./src
OBJ := ./obj
BIN := ./bin

FILENAME   := main
EXECUTABLE := $(BIN)/$(FILENAME).elf

SOURCES := $(shell find $(SRC) -name "*.c")
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

define HELP_BODY
- build: compile, link and copy needed sections into hex file
- compile: compile source files into object files
- run: run executable using $(DEBUGGER)
- debug: run debugging session
- clean: clean $(OBJ) and $(BIN) directories
- help: show help
endef
export HELP_BODY

.PHONY: help
default: run

build: compile | $(BIN)
	@echo "Linking all object files and libraries into $(EXECUTABLE) executable"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(EXECUTABLE): build

compile: $(OBJECTS)

help:
	@echo "$$HELP_BODY"

run: $(EXECUTABLE)
	@echo "Executing $(EXECUTABLE)"
	@./$(EXECUTABLE)

debug: $(EXECUTABLE)
	@echo "Starting $(DEBUGGER) session"
	@$(DEBUGGER) $(EXECUTABLE)

clean:
	@echo "Cleaning object files in $(OBJ) and executables in $(BIN)"
	@rm -rf $(OBJECTS) $(EXECUTABLE)

$(OBJECTS): | $(OBJ)

$(OBJ)/%.o: $(SRC)/%.c
	@echo "Compiling $< into $@"
	@dirname $@ | xargs mkdir -p
	@$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ):
	@echo "Creating $(OBJ) directory for object files"
	@mkdir -p $(OBJ)

$(BIN):
	@echo "Creating $(BIN) directory for binary files"
	@mkdir -p $(BIN)
