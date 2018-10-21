###############################################################################
#                                                                             #
# MAKEFILE for rtwc - A weather station with a real-time scheduler            #
#                                                                             #
# Guy Wilson (c) 2018                                                         #
#                                                                             #
###############################################################################

PROJNAME=avrw

# Target device
DEVICE=atmega328p

# Target architecture size
ARCHSIZE=8

# What is our target
ELF=$(PROJNAME).elf
TARGET=$(PROJNAME).hex

# Build output directory
BUILD=build

# Source directory
SRC=src

# Port we use to upload the tearget to the device
UPLOADPORT=/dev/cu.wchusbserial1410
#UPLOADPORT=/dev/cu.usbmodem1411

# C compiler
CC=avr-gcc

# Linker
LINKER=avr-gcc

# Hex file creator
OBJCOPY=avr-objcopy

# Assembly dump tool
OBJDUMP=avr-objdump

# Size tool
SIZETOOL=avr-size

# Upload tool
UPLOADTOOL=upload.sh

# C compiler flags
CFLAGS=-c -Os -Wall -ffunction-sections -fdata-sections -mmcu=$(DEVICE) -DF_CPU=16000000L -DARDUINO=10804 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR -DARCH_SIZE=$(ARCHSIZE)

# Linker flags
LFLAGS=-fuse-linker-plugin -Wl,--gc-sections -mmcu=$(DEVICE)

# Hex file creator flags
OBJCOPYFLAGS=-O ihex -R .eeprom

#Obj dump flags
OBJDUMPFLAGS=-I $(SRC) -f -s -l -S

# Size tool flags
SFLAGS=-C --mcu=$(DEVICE)

# Scheduler object files
SCHEDOBJ=$(BUILD)/scheduler.o

# Object files
OBJFILES=$(SCHEDOBJ) $(BUILD)/led_utils.o $(BUILD)/heartbeat.o $(BUILD)/adctask.o $(BUILD)/anemometer.o $(BUILD)/rainguage.o $(BUILD)/rtc_atmega328p.o $(BUILD)/serial_atmega328p.o $(BUILD)/adc_atmega328p.o $(BUILD)/spi_atmega328p.o $(BUILD)/error_atmega328p.o $(BUILD)/txtask.o $(BUILD)/main.o

# Target
all: $(TARGET)

###############################################################################
#
# Scheduler files
#
###############################################################################
$(BUILD)/scheduler.o: $(SRC)/scheduler.c $(SRC)/scheduler.h $(SRC)/error.h
	$(CC) $(CFLAGS) -o $(BUILD)/scheduler.o $(SRC)/scheduler.c

###############################################################################
#
# Project files
#
###############################################################################
$(BUILD)/led_utils.o: $(SRC)/led_utils.c $(SRC)/led_utils.h
	$(CC) $(CFLAGS) -o $(BUILD)/led_utils.o $(SRC)/led_utils.c

$(BUILD)/heartbeat.o: $(SRC)/heartbeat.c $(SRC)/heartbeat.h $(SRC)/led_utils.h $(SRC)/scheduler.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/heartbeat.o $(SRC)/heartbeat.c

$(BUILD)/adctask.o: $(SRC)/adctask.c $(SRC)/adctask.h $(SRC)/scheduler.h $(SRC)/taskdef.h $(SRC)/adc_atmega328p.h $(SRC)/templookup.h $(SRC)/mbarlookup.h $(SRC)/humiditylookup.h
	$(CC) $(CFLAGS) -o $(BUILD)/adctask.o $(SRC)/adctask.c

$(BUILD)/anemometer.o: $(SRC)/anemometer.c $(SRC)/anemometer.h $(SRC)/spi_atmega328p.h $(SRC)/kphlookup.h $(SRC)/taskdef.h $(SRC)/scheduler.h
	$(CC) $(CFLAGS) -o $(BUILD)/anemometer.o $(SRC)/anemometer.c

$(BUILD)/rainguage.o: $(SRC)/rainguage.c $(SRC)/rainguage.h $(SRC)/rainfall.h $(SRC)/spi_atmega328p.h $(SRC)/taskdef.h $(SRC)/scheduler.h
	$(CC) $(CFLAGS) -o $(BUILD)/rainguage.o $(SRC)/rainguage.c

$(BUILD)/rtc_atmega328p.o: $(SRC)/rtc_atmega328p.c $(SRC)/rtc_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/rtc_atmega328p.o $(SRC)/rtc_atmega328p.c

$(BUILD)/adc_atmega328p.o: $(SRC)/adc_atmega328p.c $(SRC)/adc_atmega328p.h $(SRC)/scheduler.h $(SRC)/adctask.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/adc_atmega328p.o $(SRC)/adc_atmega328p.c

$(BUILD)/spi_atmega328p.o: $(SRC)/spi_atmega328p.c $(SRC)/spi_atmega328p.h $(SRC)/scheduler.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/spi_atmega328p.o $(SRC)/spi_atmega328p.c

$(BUILD)/serial_atmega328p.o: $(SRC)/serial_atmega328p.c $(SRC)/serial_atmega328p.h $(SRC)/rxtxmsgdef.h $(SRC)/scheduler.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/serial_atmega328p.o $(SRC)/serial_atmega328p.c

$(BUILD)/error_atmega328p.o: $(SRC)/error_atmega328p.c $(SRC)/error.h $(SRC)/led_utils.h
	$(CC) $(CFLAGS) -o $(BUILD)/error_atmega328p.o $(SRC)/error_atmega328p.c

$(BUILD)/txtask.o: $(SRC)/txtask.c $(SRC)/txtask.h $(SRC)/taskdef.h $(SRC)/serial_atmega328p.h $(SRC)/adctask.h $(SRC)/anemometer.h $(SRC)/rainguage.h
	$(CC) $(CFLAGS) -o $(BUILD)/txtask.o $(SRC)/txtask.c

$(BUILD)/main.o: $(SRC)/main.c $(SRC)/scheduler.h $(SRC)/heartbeat.h $(SRC)/adctask.h $(SRC)/anemometer.h $(SRC)/rainguage.h $(SRC)/taskdef.h $(SRC)/led_utils.h $(SRC)/rtc_atmega328p.h $(SRC)/adc_atmega328p.h $(SRC)/spi_atmega328p.h $(SRC)/error.h
	$(CC) $(CFLAGS) -o $(BUILD)/main.o $(SRC)/main.c

###############################################################################
#
# Link it all together into an ELF format file
#
###############################################################################
$(BUILD)/$(ELF): $(OBJFILES)
	$(LINKER) $(LFLAGS) -o $(BUILD)/$(ELF) $(OBJFILES) -lm
	$(OBJDUMP) $(OBJDUMPFLAGS) $(BUILD)/$(ELF) > $(PROJNAME).s

###############################################################################
#
# Create the target
#
###############################################################################
$(TARGET): $(BUILD)/$(ELF)
	$(OBJCOPY) $(OBJCOPYFLAGS) $(BUILD)/$(ELF) $(TARGET)
	$(SIZETOOL) $(SFLAGS) $(BUILD)/$(ELF)

###############################################################################
#
# Upload to the device, use 'make install' to envoke
#
###############################################################################
install: $(TARGET)
	$(UPLOADTOOL) $(DEVICE) $(TARGET) $(UPLOADPORT)
	
clean: 
	rm $(BUILD)/*
	rm $(PROJNAME).s
	rm $(TARGET)
