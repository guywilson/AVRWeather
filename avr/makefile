###############################################################################
#                                                                             #
# MAKEFILE for rtwc - A weather station with a real-time scheduler            #
#                                                                             #
# Guy Wilson (c) 2018                                                         #
#                                                                             #
###############################################################################

# Version number for WCTL
MAJOR_VERSION = 1
MINOR_VERSION = 4

PROJNAME = avrw
DEVICE = atmega328p
BOARD = ARDUINO_AVR_UNO
BAUD = 115200
BAUD_TOL = 0
ARCHSIZE = 8

# What is our target
ELF = $(PROJNAME).elf
TARGET = $(PROJNAME).hex

# Directories
BUILD = build
SOURCE = src
DEP = dep

# Tools
CC = avr-gcc
LINKER = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZETOOL = avr-size
UPLOADTOOL = ./upload.sh
VBUILD = vbuild

# postcompile step
PRECOMPILE = @ mkdir -p $(BUILD) $(DEP)

# postcompile step
POSTCOMPILE = @ mv -f $(DEP)/$*.Td $(DEP)/$*.d

CFLAGS = -c -O1 -Wall -ffunction-sections -fdata-sections -mmcu=$(DEVICE) -DF_CPU=16000000L -DARDUINO=10804 -D$(BOARD) -DARDUINO_ARCH_AVR -DARCH_SIZE=$(ARCHSIZE) -DBAUD=$(BAUD) -DBAUD_TOL=$(BAUD_TOL)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP)/$*.Td
LFLAGS = -fuse-linker-plugin -Wl,--gc-sections -mmcu=$(DEVICE)
OBJCOPYFLAGS = -O ihex -R .eeprom
OBJDUMPFLAGS = -I $(SRC) -f -s -l -S
SFLAGS = -C --mcu=$(DEVICE)

# Libraries
STDLIBS = -lm -lsched

COMPILE.c = $(CC) $(CFLAGS) $(DEPFLAGS) -o $@
LINK.o = $(LINKER) $(LFLAGS) -o $@

CSRCFILES = $(wildcard $(SOURCE)/*.c)
OBJFILES = $(patsubst $(SOURCE)/%.c, $(BUILD)/%.o, $(CSRCFILES))
DEPFILES = $(patsubst $(SOURCE)/%.c, $(DEP)/%.d, $(CSRCFILES))

# Target
all: $(TARGET)

###############################################################################
#
# Create the target
#
###############################################################################
$(TARGET): $(BUILD)/$(ELF)
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@
	$(SIZETOOL) $(SFLAGS) $<

###############################################################################
#
# Link it all together into an ELF format file
#
###############################################################################
$(BUILD)/$(ELF): $(OBJFILES)
	$(LINK.o) $^ $(STDLIBS)
	$(OBJDUMP) $(OBJDUMPFLAGS) $@ > $(PROJNAME).s

###############################################################################
#
# C Project files
#
###############################################################################
$(BUILD)/%.o: $(SOURCE)/%.c
$(BUILD)/%.o: $(SOURCE)/%.c $(DEP)/%.d
	$(PRECOMPILE)
	$(COMPILE.c) $<
	$(POSTCOMPILE)

.PRECIOUS = $(DEP)/%.d
$(DEP)/%.d: ;

-include $(DEPFILES)

###############################################################################
#
# Upload to the device, use 'make install' to envoke
#
###############################################################################
install: $(TARGET)
	$(UPLOADTOOL) $(DEVICE) $(TARGET)
	
version:
	$(VBUILD) -incfile avrw.ver -template version.c.template -out $(SOURCE)/version.c -major $(MAJOR_VERSION) -minor $(MINOR_VERSION)

clean: 
	rm $(BUILD)/*
	rm $(PROJNAME).s
	rm $(TARGET)
