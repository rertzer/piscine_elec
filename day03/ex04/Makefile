CC := avr-gcc

# mmcu: AVR instruction set architecture

FREQ := 16000000UL

CFLAGS := -mmcu=atmega328p -DF_CPU=$(FREQ) -Os 

SOURCES := main.c

BIN := $(SOURCES:.c=.bin)

DOTHEX := $(SOURCES:.c=.hex)

all : hex flash

hex: $(DOTHEX)

%.bin: %.c main.h
	$(CC) $(CFLAGS) $(SOURCES) -o main.bin

%.hex: %.bin
	avr-objcopy -R eeprom -O ihex main.bin main.hex

flash:
	@killall screen 2> /dev/null || true
	avrdude -c arduino -b 115200 -p atmega328p -P /dev/ttyUSB0 -U flash:w:main.hex

clean:
	rm -f main.bin main.hex

.PHONY: all clean flash hex
