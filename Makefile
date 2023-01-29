CC ?= gcc
AR ?= ar

BIN ?= bcbasic
BIN.bcbasic ?= lib$(BIN).a
ifndef OS
    BIN.shell ?= $(BIN)
else
    BIN.shell ?= $(BIN).exe
endif

SRC ?= src
OBJ ?= obj
SRC.bcbasic ?= $(SRC)/bcbasic
OBJ.bcbasic ?= $(OBJ)/bcbasic
SRC.shell ?= $(SRC)/shell
OBJ.shell ?= $(OBJ)/shell

CFLAGS   := -Wall -Wextra -I$(SRC) -O2 $(CFLAGS)
CPPFLAGS := $(CPPFLAGS)
LDFLAGS  := $(LDFLAGS)
LDLIBS   := $(LDLIBS)
CFLAGS.bcbasic   := $(CFLAGS) $(CFLAGS.bcbasic)
CPPFLAGS.bcbasic := $(CPPFLAGS) $(CPPFLAGS.bcbasic)
LDFLAGS.bcbasic  := $(LDFLAGS) $(LDFLAGS.bcbasic)
LDLIBS.bcbasic   := $(LDLIBS) $(LDLIBS.bcbasic)
CFLAGS.shell   := $(CFLAGS) $(CFLAGS.shell)
CPPFLAGS.shell := $(CPPFLAGS) $(CPPFLAGS.shell)
LDFLAGS.shell  := $(LDFLAGS) -L. $(LDFLAGS.shell)
LDLIBS.shell   := $(LDLIBS) -lbcbasic $(LDLIBS.shell)

SOURCES.bcbasic := $(wildcard $(SRC.bcbasic)/*.c)
DEPENDS.bcbasic := Makefile $(wildcard $(SRC.bcbasic)/*.h)
OBJECTS.bcbasic := $(patsubst $(SRC.bcbasic)/%.c,$(OBJ.bcbasic)/%.o,$(SOURCES.bcbasic))
SOURCES.shell := $(wildcard $(SRC.shell)/*.c)
DEPENDS.shell := Makefile $(wildcard $(SRC.shell)/*.h)
OBJECTS.shell := $(patsubst $(SRC.shell)/%.c,$(OBJ.shell)/%.o,$(SOURCES.shell))

build: $(BIN.bcbasic) $(BIN.shell)

run: $(BIN.shell)
	@echo Running binary $<...
	@./$<
	@echo Binary $< exited successfully

$(BIN.bcbasic): $(OBJECTS.bcbasic)
	@echo Building binary $@ from $^...
	@$(AR) rs $@ $^
	@echo Built binary $@

$(OBJ.bcbasic)/%.o: $(SRC.bcbasic)/%.c $(DEPENDS.bcbasic) | $(OBJ)
	@echo Compiling object $@ from $<...
	@$(CC) $(CPPFLAGS.bcbasic) $(CFLAGS.bcbasic) -c -o $@ $<
	@echo Compiled object $@

$(BIN.shell): $(OBJECTS.shell) $(BIN.bcbasic)
	@echo Building binary $@ from $^...
	@$(CC) $(LDFLAGS.shell) $(LDLIBS.shell) -o $@ $(filter %.o,$^)
	@echo Built binary $@

$(OBJ.shell)/%.o: $(SRC.shell)/%.c $(DEPENDS.shell) | $(OBJ)
	@echo Compiling object $@ from $<...
	@$(CC) $(CPPFLAGS.shell) $(CFLAGS.shell) -c -o $@ $<
	@echo Compiled object $@

$(OBJ):
ifndef OS
	@[ ! -d $(OBJ) ] && mkdir -p $(OBJ); true
	@[ ! -d $(OBJ.bcbasic) ] && mkdir -p $(OBJ.bcbasic); true
	@[ ! -d $(OBJ.shell) ] && mkdir -p $(OBJ.shell); true
else
	@if not exist $(OBJ) (mkdir $(OBJ))
	@if not exist $(OBJ.bcbasic) (mkdir $(OBJ.bcbasic))
	@if not exist $(OBJ.shell) (mkdir $(OBJ.shell))
endif

clean:
ifndef OS
	@rm -rf $(BIN) $(OBJ)/
else
	@if exist $(BIN) (del /Q $(BIN))
	@if exist $(OBJ) (rmdir /S /Q $(OBJ))
endif

.PHONY: all run clean $(OBJ)

