###############################################################################
#                                                                             #
# MAKEFILE for rtwc - A weather station with a real-time scheduler            #
#                                                                             #
# Guy Wilson (c) 2018                                                         #
#                                                                             #
###############################################################################

# Version number for WCTL
MAJOR_VERSION=1
MINOR_VERSION=2

PROJNAME=avrw

# Target device
DEVICE=atmega328p

# Target board
BOARD=ARDUINO_AVR_UNO

# Baud rate for serial comms
BAUD=115200

# Baud rate tolerance for serial comms
BAUD_TOL=0

# Target architecture size
ARCHSIZE=8

# What is our target
ELF=$(PROJNAME).elf
TARGET=$(PROJNAME).hex

# Build output directory
BUILD=build

# Source directory
SRC=src

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
UPLOADTOOL=./upload.sh

VBUILD=vbuild

# C compiler flags
CFLAGS=-c -O1 -Wall -ffunction-sections -fdata-sections -mmcu=$(DEVICE) -DF_CPU=16000000L -DARDUINO=10804 -D$(BOARD) -DARDUINO_ARCH_AVR -DARCH_SIZE=$(ARCHSIZE)

# Linker flags
LFLAGS=-fuse-linker-plugin -Wl,--gc-sections -mmcu=$(DEVICE)

# Hex file creator flags
OBJCOPYFLAGS=-O ihex -R .eeprom

#Obj dump flags
OBJDUMPFLAGS=-I $(SRC) -f -s -l -S

# Size tool flags
SFLAGS=-C --mcu=$(DEVICE)

# Object files
OBJFILES=$(BUILD)/led_utils.o $(BUILD)/heartbeat.o $(BUILD)/wdttask.o $(BUILD)/adctask.o $(BUILD)/anemometer.o $(BUILD)/rainguage.o $(BUILD)/wdt_atmega328p.o $(BUILD)/isr_atmega328p.o $(BUILD)/rtc_atmega328p.o $(BUILD)/serial_atmega328p.o $(BUILD)/adc_atmega328p.o $(BUILD)/extint_atmega328p.o $(BUILD)/pwm_atmega328p.o $(BUILD)/error_atmega328p.o $(BUILD)/rxtxtask.o $(BUILD)/main.o

# Target
all: $(TARGET)

###############################################################################
#
# Project files
#
###############################################################################
$(BUILD)/led_utils.o: $(SRC)/led_utils.c $(SRC)/led_utils.h
	$(CC) $(CFLAGS) -o $(BUILD)/led_utils.o $(SRC)/led_utils.c

$(BUILD)/heartbeat.o: $(SRC)/heartbeat.c $(SRC)/heartbeat.h $(SRC)/led_utils.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/heartbeat.o $(SRC)/heartbeat.c

$(BUILD)/wdttask.o: $(SRC)/wdttask.c $(SRC)/wdttask.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/wdttask.o $(SRC)/wdttask.c

$(BUILD)/adctask.o: $(SRC)/adctask.c $(SRC)/adctask.h $(SRC)/taskdef.h $(SRC)/adc_atmega328p.h $(SRC)/templookup.h $(SRC)/mbarlookup.h $(SRC)/humiditylookup.h
	$(CC) $(CFLAGS) -o $(BUILD)/adctask.o $(SRC)/adctask.c

$(BUILD)/anemometer.o: $(SRC)/anemometer.c $(SRC)/anemometer.h $(SRC)/spi_atmega328p.h $(SRC)/kphlookup.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/anemometer.o $(SRC)/anemometer.c

$(BUILD)/rainguage.o: $(SRC)/rainguage.c $(SRC)/rainguage.h $(SRC)/rainfall.h $(SRC)/spi_atmega328p.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/rainguage.o $(SRC)/rainguage.c

$(BUILD)/wdt_atmega328p.o: $(SRC)/wdt_atmega328p.c $(SRC)/wdt_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/wdt_atmega328p.o $(SRC)/wdt_atmega328p.c

$(BUILD)/isr_atmega328p.o: $(SRC)/isr_atmega328p.c $(SRC)/rtc_atmega328p.h $(SRC)/adc_atmega328p.h $(SRC)/serial_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/isr_atmega328p.o $(SRC)/isr_atmega328p.c

$(BUILD)/rtc_atmega328p.o: $(SRC)/rtc_atmega328p.c $(SRC)/rtc_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/rtc_atmega328p.o $(SRC)/rtc_atmega328p.c

$(BUILD)/extint_atmega328p.o: $(SRC)/extint_atmega328p.c $(SRC)/extint_atmega328p.h $(SRC)/rtc_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/extint_atmega328p.o $(SRC)/extint_atmega328p.c

$(BUILD)/adc_atmega328p.o: $(SRC)/adc_atmega328p.c $(SRC)/adc_atmega328p.h $(SRC)/adctask.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -o $(BUILD)/adc_atmega328p.o $(SRC)/adc_atmega328p.c

$(BUILD)/pwm_atmega328p.o: $(SRC)/pwm_atmega328p.c $(SRC)/pwm_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/pwm_atmega328p.o $(SRC)/pwm_atmega328p.c

$(BUILD)/serial_atmega328p.o: $(SRC)/serial_atmega328p.c $(SRC)/serial_atmega328p.h $(SRC)/rtc_atmega328p.h $(SRC)/rxtxmsgdef.h $(SRC)/taskdef.h
	$(CC) $(CFLAGS) -DBAUD=$(BAUD) -DBAUD_TOL=$(BAUD_TOL) -o $(BUILD)/serial_atmega328p.o $(SRC)/serial_atmega328p.c

$(BUILD)/error_atmega328p.o: $(SRC)/error_atmega328p.c $(SRC)/led_utils.h
	$(CC) $(CFLAGS) -o $(BUILD)/error_atmega328p.o $(SRC)/error_atmega328p.c

$(BUILD)/rxtxtask.o: $(SRC)/rxtxtask.c $(SRC)/rxtxtask.h $(SRC)/taskdef.h $(SRC)/serial_atmega328p.h $(SRC)/adctask.h $(SRC)/anemometer.h $(SRC)/rainguage.h
	$(CC) $(CFLAGS) -o $(BUILD)/rxtxtask.o $(SRC)/rxtxtask.c

$(BUILD)/main.o: $(SRC)/main.c $(SRC)/heartbeat.h $(SRC)/wdttask.h $(SRC)/adctask.h $(SRC)/anemometer.h $(SRC)/rainguage.h $(SRC)/taskdef.h $(SRC)/led_utils.h $(SRC)/wdt_atmega328p.h $(SRC)/rtc_atmega328p.h $(SRC)/adc_atmega328p.h $(SRC)/extint_atmega328p.h $(SRC)/pwm_atmega328p.h $(SRC)/spi_atmega328p.h
	$(CC) $(CFLAGS) -o $(BUILD)/main.o $(SRC)/main.c

###############################################################################
#
# Link it all together into an ELF format file
#
###############################################################################
$(BUILD)/$(ELF): $(OBJFILES)
	$(VBUILD) -incfile avrw.ver -template version.c.template -out $(SRC)/version.c -major $(MAJOR_VERSION) -minor $(MINOR_VERSION)
	$(CC) $(CFLAGS) -o $(BUILD)/version.o $(SRC)/version.c
	$(LINKER) $(LFLAGS) -o $(BUILD)/$(ELF) $(OBJFILES) $(BUILD)/version.o -lm -lsched
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
	$(UPLOADTOOL) $(DEVICE) $(TARGET)
	
clean: 
	rm $(BUILD)/*
	rm $(PROJNAME).s
	rm $(TARGET)
