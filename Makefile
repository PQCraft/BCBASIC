BIN = bcbasic

ifdef OS
BIN = $(BIN).exe
endif

ifndef OS
CC ?= gcc
else
CC = gcc
endif

SRC = src
OBJ = obj
LIB = $(SRC)/lib
INC = $(SRC)/inc

POBJFLAGS := -Wall -Wextra -I. -I$(INC) $(POBJFLAGS)
OBJFLAGS := -O2 -s -flto $(OBJFLAGS)

PBINFLAGS := -Wall -Wextra -L. -L$(LIB) -flto $(PBINFLAGS)
BINFLAGS := -lm -lreadline $(BINFLAGS)

SOURCES := $(wildcard $(SRC)/*.c)
DEPENDS := $(wildcard $(SRC)/*.h) Makefile
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

.PHONY: all build run clean $(OBJ)

all: run

build: $(BIN)

run: $(BIN)
	@echo "Running binary $<..."
	@./$<
	@echo "Binary $< exited successfully"

$(BIN): $(OBJECTS)
	@echo "Building binary $@ from $^..."
	@$(CC) -o $@ $(PCFLAGS) $(PBINFLAGS) $^ $(CFLAGS) $(BINFLAGS)
	@echo "Built binary $@"

$(OBJ):
ifndef OS
	@[ ! -d $(OBJ) ] && mkdir -p $(OBJ); true
else
	@if not exist $(OBJ) mkdir $(OBJ)
endif

$(OBJ)/%.o: $(SRC)/%.c $(DEPENDS) | $(OBJ)
	@echo "Compiling object $@ from $<..."
	@$(CC) -o $@ $(PCFLAGS) $(POBJFLAGS) -c $< $(CFLAGS) $(OBJFLAGS)
	@echo "Compiled object $@"

clean:
ifndef OS
	@rm -rf $(BIN) $(OBJ)/
else
	@if exist $(BIN) del /Q $(BIN)
	@if exist $(OBJ) rmdir /S /Q $(OBJ)
endif

