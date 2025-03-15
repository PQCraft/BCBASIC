SRCDIR := src
OBJDIR := obj
INCDIR := include
OUTDIR := .

SOURCES.lib := $(wildcard $(SRCDIR)/bcbasic/*.c)
OBJECTS.lib := $(patsubst $(SRCDIR)/bcbasic/%.c,$(OBJDIR)/bcbasic/%.o,$(SOURCES.lib))

SOURCES.sh := $(wildcard $(SRCDIR)/shell/*.c)
OBJECTS.sh := $(patsubst $(SRCDIR)/shell/%.c,$(OBJDIR)/shell/%.o,$(SOURCES.sh))

BIN := bcbasic

BIN.lib := $(OUTDIR)/lib$(BIN)
BIN.lib.a := $(BIN.lib).a
ifneq ($(OS),Windows_NT)
    BIN.lib.so := $(BIN.lib).so
else
    BIN.lib.so := $(BIN.lib).dll
endif

BIN.sh := $(OUTDIR)/$(BIN)
ifeq ($(OS),Windows_NT)
    BIN.sh := $(BIN.sh).exe
endif

CC ?= gcc
LD := $(CC)
AR := ar
STRIP ?= strip
_CC := $(TOOLCHAIN)$(CC)
_LD := $(TOOLCHAIN)$(LD)
_AR := $(TOOLCHAIN)$(AR)
_STRIP := $(TOOLCHAIN)$(STRIP)

CFLAGS += -Wall -Wextra
ifneq ($(DEBUG),y)
    CPPFLAGS += -DNDEBUG
    O := 2
else
    CFLAGS += -g -Wdouble-promotion -fno-omit-frame-pointer -std=c11 -pedantic
    O := g
endif
CFLAGS += -O$(O)
ifeq ($(ASAN),y)
    CFLAGS += -fsanitize=address
    LDFLAGS += -fsanitize=address
endif

CFLAGS.sh += -I$(SRCDIR)
LDFLAGS.sh += -L$(OUTDIR)
LDLIBS.sh += -l:libbcbasic.a

.SECONDEXPANSION:

define mkdir
if [ ! -d '$(1)' ]; then echo 'Creating $(1)/...'; mkdir -p '$(1)'; fi; true
endef
define rm
if [ -f '$(1)' ]; then echo 'Removing $(1)...'; rm -f '$(1)'; fi; true
endef
define rmdir
if [ -d '$(1)' ]; then echo 'Removing $(1)/...'; rm -rf '$(1)'; fi; true
endef

deps.filter := %.c %.h
deps.option := -MM
define deps
$$(filter $$(deps.filter),,$$(shell $(_CC) $(CFLAGS) $(2) $(CPPFLAGS) $(3) -E $(deps.option) $(1)))
endef

default: sh

$(OUTDIR):
	@$(call mkdir,$@)

$(OBJDIR)/bcbasic:
	@$(call mkdir,$@)

$(OBJDIR)/bcbasic/%.o: $(SRCDIR)/bcbasic/%.c $(call deps,$(SRCDIR)/bcbasic/%.c,$(CFLAGS.lib),$(CPPFLAGS.lib)) | $(OBJDIR)/bcbasic
	@echo Compiling $<...
	@$(_CC) $(CFLAGS) $(CFLAGS.lib) $(CPPFLAGS) $(CPPFLAGS.lib) $< -c -o $@
	@echo Compiled $<

$(BIN.lib.a): $(OBJECTS.lib) | $(OUTDIR)
	@echo Linking $@...
	@$(AR) rcs $@ $^
	@echo Linked $@

$(BIN.lib.so): $(OBJECTS.lib) | $(OUTDIR)
	@echo Linking $@...
	@$(_LD) -shared $(LDFLAGS) $(LDFLAGS.lib) $^ $(LDLIBS) $(LDLIBS.lib) -o $@
	@echo Linked $@

$(OBJDIR)/shell:
	@$(call mkdir,$@)

$(OBJDIR)/shell/%.o: $(SRCDIR)/shell/%.c $(call deps,$(SRCDIR)/shell/%.c,$(CFLAGS.sh),$(CPPFLAGS.sh)) | $(OBJDIR)/shell
	@echo Compiling $<...
	@$(_CC) $(CFLAGS) $(CFLAGS.sh) $(CPPFLAGS) $(CPPFLAGS.sh) $< -c -o $@
	@echo Compiled $<

$(BIN.sh): $(OBJECTS.sh) $(BIN.lib.a) | $(OUTDIR)
	@echo Linking $@...
	@$(_LD) $(LDFLAGS) $(LDFLAGS.sh) $^ $(LDLIBS) $(LDLIBS.sh) -o $@
ifneq ($(NOSTRIP),y)
	@$(_STRIP) -s -R '.comment' -R '.note.*' -R '.gnu.build-id' $@ || exit 0
endif
	@echo Linked $@

all: $(BIN.lib.a) $(BIN.lib.so) $(BIN.sh)
	@:

lib library: $(BIN.lib.a) $(BIN.lib.so)
	@:

lib.a static_library: $(BIN.lib.a)
	@:

lib.so shared_library: $(BIN.lib.so)
	@:

sh shell: $(BIN.sh)
	@:

clean:
	@$(call rmdir,$(OBJDIR))

distclean: clean
	@$(call rm,$(BIN.lib.a))
	@$(call rm,$(BIN.lib.so))
	@$(call rm,$(BIN.sh))

SYSINC := /usr/include
SYSLIB := /usr/lib
SYSBIN := /usr/bin

install:
	@echo Installing headers...; mkdir '$(SYSINC)/bcbasic'; cp -rf '$(SRCDIR)/bcbasic'/*.h '$(SYSINC)/bcbasic'
	@if [ -f '$(BIN.lib.a)' ]; then echo Installing static library...; cp -f '$(BIN.lib.a)' '$(SYSLIB)'; fi
	@if [ -f '$(BIN.lib.so)' ]; then echo Installing shared library...; cp -f '$(BIN.lib.so)' '$(SYSLIB)'; fi
	@if [ -f '$(BIN.sh)' ]; then echo Installing shell...; cp -f '$(BIN.sh)' '$(SYSBIN)'; fi

uninstall:
	@echo Uninstalling headers...; rm -rf '$(SYSINC)/bcbasic'
	@if [ -f '$(SYSLIB)/$(BIN.lib.a)' ]; then echo Uninstalling static library...; rm -f '$(SYSLIB)/$(BIN.lib.a)'; fi
	@if [ -f '$(SYSLIB)/$(BIN.lib.so)' ]; then echo Uninstalling shared library...; rm -f '$(SYSLIB)/$(BIN.lib.so)'; fi
	@if [ -f '$(SYSBIN)/$(BIN.sh)' ]; then echo Uninstalling shell...; rm -f '$(SYSBIN)/$(BIN.sh)'; fi

.PHONY: default all lib library lib.a static_library lib.so shared_library sh shell clean distclean install uninstall
