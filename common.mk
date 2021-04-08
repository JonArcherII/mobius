CC      := i686-elf-gcc
CXX     := i686-elf-g++
AS      := i686-elf-as
LD      := i686-elf-g++
AR      := i686-elf-ar

SRC_DIRS ?= .

SOURCES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
SOURCES += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
SOURCES += $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.s))

OBJECTS := $(filter %.o, $(patsubst %.c, %.o, $(SOURCES)))
OBJECTS += $(filter %.o, $(patsubst %.cpp, %.o, $(SOURCES)))
OBJECTS += $(filter %.o, $(patsubst %.s, %.o, $(SOURCES)))

CFLAGS          := -std=c11
CXXFLAGS        := -std=c++11 -fno-rtti
CPPFLAGS        := -fno-stack-protector
CPPFLAGS        += -ffreestanding -fno-exceptions
CPPFLAGS        += -mno-red-zone -m32
CPPFLAGS        += -Wall -Wextra -Og -g
CPPFLAGS        += $(foreach dir, $(SRC_DIRS), -I$(dir))
CPPFLAGS        += $(foreach def, $(DEFINES), -D$(def))

.DEFAULT_GOAL := all

.c.o:
	@echo "CC $<"; $(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ -c $<

.s.o:
	@echo "AS $<"; $(AS) $(ASFLAGS) -o $@ $<

clean:
	-@echo "CLEAN"; rm -rf $(TARGET) $(OBJECTS)

.PHONY: all clean
