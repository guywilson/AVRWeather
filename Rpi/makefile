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
OBJFILES=$(BUILD)/main.o $(BUILD)/serial.o $(BUILD)/avrweather.o $(BUILD)/webconnect.o $(BUILD)/exception.o

# Target
all: $(TARGET)

# Compile C source files
#
$(BUILD)/main.o: $(SOURCE)/main.cpp $(SOURCE)/serial.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/main.o $(SOURCE)/main.cpp

$(BUILD)/serial.o: $(SOURCE)/serial.cpp $(SOURCE)/serial.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/serial.o $(SOURCE)/serial.cpp

$(BUILD)/avrweather.o: $(SOURCE)/avrweather.cpp $(SOURCE)/avrweather.h $(SOURCE)/webconnect.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/avrweather.o $(SOURCE)/avrweather.cpp

$(BUILD)/webconnect.o: $(SOURCE)/webconnect.cpp $(SOURCE)/webconnect.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/webconnect.o $(SOURCE)/webconnect.cpp

$(BUILD)/exception.o: $(SOURCE)/exception.cpp $(SOURCE)/exception.h $(SOURCE)/types.h
	$(CPP) $(CPPFLAGS) -o $(BUILD)/exception.o $(SOURCE)/exception.cpp

$(TARGET): $(OBJFILES)
	$(LINKER) -lpthread -lstdc++ -o $(TARGET) $(OBJFILES)
