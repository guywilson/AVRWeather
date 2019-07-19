###############################################################################
#                                                                             #
# MAKEFILE for Toggle tool                                                    #
#                                                                             #
# � Guy Wilson 2019                                                           #
#                                                                             #
###############################################################################

# Source directory
SOURCE=src

# Build output directory
BUILD=build

# What is our target
TARGET=toggle

# C compiler
C=gcc

# Linker
LINKER=gcc

# C compiler flags (Release)
CFLAGS=-c -Wall

# Object files (in linker ',' seperated format)
OBJFILES=$(BUILD)/toggle.o

# Target
all: $(TARGET)

# Compile C source files
#
$(BUILD)/toggle.o: $(SOURCE)/toggle.c
	$(C) $(CFLAGS) -o $(BUILD)/toggle.o $(SOURCE)/toggle.c

$(TARGET): $(OBJFILES)
	$(LINKER) -lgpioc -o $(TARGET) $(OBJFILES)
