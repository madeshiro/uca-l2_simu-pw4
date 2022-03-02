Makefile = Makefile
Project  = projectsi_pw4

# Author : Rin Baudelet

CLEAN = clean
MRPROPER = mrproper
MKDIR = mkdir

ifeq ($(DEBUG), true)
	GDB_OPT = -g
	GDB_SUFFIX = d
	DEFINES = -DPW_DEBUG
	OUT_DIR = make_unix64_debug
else
	DEFINES = -DPW_RELEASE
	OUT_DIR = make_unix64_release
endif

#### Compiler Setting ####

CC		= gcc $(GDB_OPT)
ASM		= gcc $(GDB_OPT) -x assembler
CXX		= g++ $(GDB_OPT)
LINKER	= gcc $(GDB_OPT)
STATIC	= ar

ROOT			=
VPATH			= src/ include/
DEST_NAME		= projectsi_pw4$(GDB_SUFFIX)
DEST_TARGET		= $(DEST_NAME)$(EXE_EXTENSION)
OUT_DIR_TARGET	= $(OUT_DIR)/

LIBS   = -lm
TARGET = $(OUT_DIR_TARGET)$(DEST_TARGET)
LFLAGS = -fPIC

CSTD	 = -std=c11
CXXSTD   = -std=c++11

INCPATH  =
DEFINES  := $(DEFINES)
CFLAGS	 := $(CSTD) -Wall -Wextra -pipe $(CFLAGS) $(DEFINES)
CXXFLAGS := $(CXXSTD) -Wall -Wextra -pipe $(CXXFLAGS) $(DEFINES)

#### FILES ####

INCLUDES = mt19937ar.h

SOURCES = main.c \
			mt19937ar.c

OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

#### INSTRUCTIONS ####

first: all
all: $(MKDIR) $(TARGET)
$(TARGET): $(OBJECTS)
	$(LINKER) $(LFLAGS) -o $@ $(patsubst %.o, $(OUT_DIR_TARGET)%.o, $^) $(LIBS)
debug:
	@make -e DEBUG=true

#### OBJECTS ####

.SUFFIXES: .c
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(OUT_DIR_TARGET)$@

.PHONY: clean mrproper
clean:
	@rm -f $(OUT_DIR)/*.o
mrproper: clean
	@rm -f $(TARGET)
mkdir:
	@mkdir -p $(OUT_DIR)

run:
	@./$(TARGET)