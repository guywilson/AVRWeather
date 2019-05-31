###############################################################################
#                                                                             #
# MAKEFILE for Rpi end of AVRWeather                                          #
#                                                                             #
# (c) Guy Wilson 2019                                                         #
#                                                                             #
###############################################################################

# Source directory
SOURCE=src

# Build output directory
BUILD=build

# What is our target
TARGET=wctl

# C compiler
CPP=gcc

# Linker
LINKER=gcc

# C compiler flags (Release)
CPPFLAGS=-c -Wall

# Object files 
OBJFILES=$(BUILD)/main.o

# Target
all: $(TARGET)

# Compile C source files
#
$(BUILD)/main.o: $(SOURCE)/main.c $(SOURCE)/rxtxmsgdef.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/main.o $(SOURCE)/main.c

$(TARGET): $(OBJFILES)
	$(LINKER) -lpthread -lstdc++ -o $(TARGET) $(OBJFILES)
