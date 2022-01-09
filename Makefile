ifndef OS
BIN := bcbasic
else
BIN := bcbasic.exe
endif

POBJFLAGS := -Wall -Wextra -I. -I./src/include $(POBJFLAGS)
OBJFLAGS := -O2 -s -flto $(OBJFLAGS)

PBINFLAGS := -Wall -Wextra -L. -L./src/lib -flto $(PBINFLAGS)
BINFLAGS := -lm $(BINFLAGS)

SRC := src
OBJ := obj

SOURCES := $(wildcard $(SRC)/*.c)
DEPENDS := $(wildcard $(SRC)/*.h)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

ifdef CC
CC := gcc
endif

.PHONY: all build run clean $(OBJ)

all: run

build: $(BIN)

run: $(BIN)
	@echo "Running binary \"./$<\""
	@./$<
	@echo "\"./$<\" exited successfully"

$(BIN): $(OBJECTS)
	@echo "Building binary \"$@\" from \"$^\""
	@$(CC) -o $@ $(PCFLAGS) $(PBINFLAGS) $^ $(CFLAGS) $(BINFLAGS)
	@echo "Built binary \"$@\""

$(OBJ):
ifndef OS
	@[ ! -d $(OBJ) ] && mkdir -p $(OBJ); true
else
	@if not exist $(OBJ) mkdir $(OBJ)
endif

$(OBJ)/%.o: $(SRC)/%.c $(DEPENDS) | $(OBJ)
	@echo "Compiling object \"$@\" from \"$<\""
	@$(CC) -o $@ $(PCFLAGS) $(POBJFLAGS) -c $< $(CFLAGS) $(OBJFLAGS)
	@echo "Compiled object \"$@\""

clean:
ifndef OS
	@rm -rf $(BIN) $(OBJ)/
else
	@if exist $(BIN) del /Q $(BIN)
	@if exist $(OBJ) rmdir /S /Q $(OBJ)
endif

