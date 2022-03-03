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
			defines.h \
			utils.h \
			cxx/entities.h \
			cxx/simulation.h \
			cxx/entities_ai.h \
			cxx/application.h \
			cxx/oop/container.h \
			cxx/oop/exception.h \
			cxx/oop/object.h \
			cxx/oop/type_traits.hpp \
			cxx/oop/string.hpp \
			cxx/oop/stream.h \
			cxx/json/json.h \
			cxx/json/jsonvalue.h

SOURCES = main.cpp \
			mt19937ar.c \
			utils.c \
			cxx/entities.cpp \
			cxx/simulation.cpp \
			cxx/entities_ai.cpp \
			cxx/application.cpp \
			cxx/oop/exception.cpp \
			cxx/oop/object.cpp \
			cxx/oop/stream.cpp \
			cxx/oop/string.c++ \
			cxx/json/json.cpp \
			cxx/json/jsonvalue.cpp

OBJECTS  = main.cpp.o \
			entities.cpp.o \
			simulation.cpp.o \
			entities_ai.cpp.o \
			application.cpp.o \
			object.cpp.o \
			stream.cpp.o \
			exception.cpp.o \
			jsonvalue.cpp.o \
			json.cpp.o \
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

#### > Project (simulation) Files
main.cpp.o: main.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
entities.cpp.o: cxx/entities.cpp cxx/entities.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
simulation.cpp.o: cxx/simulation.cpp cxx/simulation.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
simulation.cpp.o: cxx/exception.cpp cxx/exception.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
entities_ai.cpp.o: cxx/entities_ai.cpp cxx/entities_ai.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
application.cpp.o: cxx/application.cpp cxx/application.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@

#### > OOP
object.cpp.o: cxx/oop/object.cpp cxx/oop/object.h cxx/oop/string.c++ defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
exception.cpp.o: cxx/oop/exception.cpp cxx/oop/exception.h cxx/oop/object.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
string.c++.o: cxx/oop/string.c++ cxx/oop/string.h cxx/oop/object.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
stream.cpp.o: cxx/oop/stream.cpp cxx/oop/stream.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@

#### > json
jsonvalue.cpp.o: cxx/json/jsonvalue.cpp cxx/json/jsonvalue.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
json.cpp.o: cxx/json/json.cpp cxx/json/json.h defines.h cxx/oop/object.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@

#### > C Files
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