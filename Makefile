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
	OUT_DIR = build_unix64_debug
else
	DEFINES = -DPW_RELEASE
	OUT_DIR = build_unix64_release
endif

#### Compiler Setting ####

CC		= gcc $(GDB_OPT)
ASM		= gcc $(GDB_OPT) -x assembler
CXX		= g++ $(GDB_OPT)
LINKER	= g++ $(GDB_OPT)
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

INCPATH  = -Iinclude/
DEFINES  := $(DEFINES)
CFLAGS	 := $(CSTD) -Wall -Wextra -pipe $(CFLAGS) $(INCPATH) $(DEFINES)
CXXFLAGS := $(CXXSTD) -Wall -Wextra -pipe $(CXXFLAGS) $(INCPATH) $(DEFINES)

#### FILES ####

INCLUDES = mt19937ar.h \
			entities.h \
			defines.h \
			utils.h \
			simulation.h

SOURCES = main.cpp \
			entities/entities.cpp \
			simulation.cpp \
			mt19937ar.c \
			utils.c

OBJECTS  = main.cpp.o \
			entities.cpp.o \
			simulation.cpp.o \
			mt19937ar.c.o \
			utils.c.o

#### INSTRUCTIONS ####

first: all
all: $(MKDIR) $(TARGET)
$(TARGET): $(OBJECTS)
	$(LINKER) $(LFLAGS) -o $@ $(patsubst %.o, $(OUT_DIR_TARGET)%.o, $^) $(LIBS)
debug:
	@make -e DEBUG=true

#### OBJECTS ####

main.cpp.o: main.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
entities.cpp.o: entities/entities.cpp entities.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
rabbit.cpp.o: entities/rabbit.cpp entities.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
simulation.cpp.o: simulation.cpp simulation.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@

mt19937ar.c.o: mt19937ar.c mt19937ar.h
	$(CC) $(CFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
utils.c.o: utils.c utils.h defines.h
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