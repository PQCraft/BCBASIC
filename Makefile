ifndef OS
CC ?= gcc
else
BINEXT = .exe
CC = gcc
endif

BIN = bcbasic$(BINEXT)

SRC ?= src
OBJ ?= obj
LIB += lib
INC += inc

INCO = $(patsubst %,-I%,$(INC))
LIBO = $(patsubst %,-L%,$(LIB))

POBJFLAGS := -Wall -Wextra -std=c99 -DBCB_STANDALONE -I. $(INCO) $(POBJFLAGS)
OBJFLAGS := -O2 -s -flto $(OBJFLAGS)

PBINFLAGS := -Wall -Wextra -L. $(LIBO) -flto $(PBINFLAGS)
BINFLAGS := -lm $(BINFLAGS)

SOURCES := $(wildcard $(SRC)/*.c)
DEPENDS := $(wildcard $(SRC)/*.h) Makefile
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: build

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

.PHONY: all build run clean $(OBJ)

