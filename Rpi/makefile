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
CPP=g++

# Linker
LINKER=g++

# C compiler flags (Release)
CPPFLAGS=-c -O3 -fpermissive -fPIC -Wall -std=c++11

# Object files 
OBJFILES=$(BUILD)/main.o $(BUILD)/serial.o $(BUILD)/exception.o $(BUILD)/stack.o

# Target
all: $(TARGET)

# Compile C source files
#
$(BUILD)/main.o: $(SOURCE)/main.cpp $(SOURCE)/serial.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/main.o $(SOURCE)/main.cpp

$(BUILD)/serial.o: $(SOURCE)/serial.cpp $(SOURCE)/serial.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/serial.o $(SOURCE)/serial.cpp

$(BUILD)/exception.o: $(SOURCE)/exception.cpp $(SOURCE)/exception.h $(SOURCE)/types.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/exception.o $(SOURCE)/exception.cpp

$(BUILD)/stack.o: $(SOURCE)/stack.cpp $(SOURCE)/stack.h $(SOURCE)/exception.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/stack.o $(SOURCE)/stack.cpp

$(TARGET): $(OBJFILES)
	$(LINKER) -lpthread -lstdc++ -o $(TARGET) $(OBJFILES)
