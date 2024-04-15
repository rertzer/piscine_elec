CC := avr-gcc

# mmcu: AVR instruction set architecture

CFLAGS := -mmcu=atmega328p

FREQ := 16000000UL

SOURCES := main.c

all : hex flash

hex:
	$(CC) $(CFLAGS) -DF_CPU=$(FREQ) $(SOURCES) -o main.bin
	avr-objcopy -R eeprom -O ihex main.bin main.hex

flash:
	avrdude -c arduino -b 115200 -p atmega328p -P /dev/ttyUSB0 -U flash:w:main.hex

clean:
	rm -f main.bin main.hex

.PHONY: all clean flash hex
