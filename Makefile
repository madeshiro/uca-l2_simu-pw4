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
			cxx/application.h \
			cxx/simulation/entities.h \
			cxx/simulation/simulation.h \
			cxx/simulation/cdfpdf.h \
			cxx/simulation/statisticaltools.h \
			cxx/oop/container.hpp \
			cxx/oop/container.hpp \
			cxx/oop/exception.h \
			cxx/oop/object.h \
			cxx/oop/binary.h \
			cxx/oop/type_traits.hpp \
			cxx/oop/string.hpp \
			cxx/oop/alloc.hpp \
			cxx/oop/stream.h \
			cxx/oop/sock.h \
			cxx/oop/file.h \
			cxx/serv/packet.h \
			cxx/json/json.h \
			cxx/json/jsonvalue.h

SOURCES = main.cpp \
			mt19937ar.c \
			utils.c \
			cxx/application.cpp \
			cxx/simulation/simulation.cpp \
			cxx/simulation/entities.cpp \
			cxx/simulation/cdfpdf.cpp \
			cxx/simulation/statisticaltools.cpp \
			cxx/oop/exception.cpp \
			cxx/oop/object.cpp \
			cxx/oop/stream.cpp \
			cxx/oop/string.c++ \
			cxx/oop/alloc.c++ \
			cxx/oop/binary.cpp \
			cxx/oop/type_traits.c++ \
			cxx/oop/sock.cpp \
			cxx/oop/file.cpp \
			cxx/serv/packet.cpp \
			cxx/json/json.cpp \
			cxx/json/jsonvalue.cpp

OBJECTS  = main.cpp.o \
			application.cpp.o \
			entities.cpp.o \
			simulation.cpp.o \
			cdfpdf.cpp.o \
			statisticaltools.cpp.o \
			object.cpp.o \
			stream.cpp.o \
			sock.cpp.o \
			event.cpp.o \
			file.cpp.o \
			exception.cpp.o \
			binary.cpp.o \
			type_traits.cpp.o \
			packet.cpp.o \
			container.cpp.o \
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
application.cpp.o: cxx/application.cpp cxx/application.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@


entities.cpp.o: cxx/simulation/entities.cpp cxx/simulation/entities.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
simulation.cpp.o: cxx/simulation/simulation.cpp cxx/simulation/simulation.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
cdfpdf.cpp.o: cxx/simulation/cdfpdf.cpp cxx/simulation/cdfpdf.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
statisticaltools.cpp.o: cxx/simulation/statisticaltools.cpp cxx/simulation/statisticaltools.h defines.h
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
file.cpp.o: cxx/oop/file.cpp cxx/oop/file.h cxx/oop/stream.h cxx/oop/object.h defines.h utils.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
sock.cpp.o: cxx/oop/sock.cpp cxx/oop/sock.h cxx/oop/stream.h cxx/oop/object.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
event.cpp.o: cxx/oop/event.c++ cxx/oop/event.hpp defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
type_traits.cpp.o: cxx/oop/type_traits.c++ cxx/oop/type_traits.hpp defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
binary.cpp.o: cxx/oop/binary.cpp cxx/oop/binary.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@

#### > serv
packet.cpp.o: cxx/serv/packet.cpp cxx/serv/packet.h cxx/oop/object.h defines.h
	$(CXX) $(CXXFLAGS) -c $< -o $(OUT_DIR_TARGET)$@
container.cpp.o: cxx/oop/container.c++ cxx/oop/container.hpp defines.h
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