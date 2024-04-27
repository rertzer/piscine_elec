CC := avr-gcc

# mmcu: AVR instruction set architecture

FREQ := 16000000UL

CFLAGS := -mmcu=atmega328p -DF_CPU=$(FREQ) -Os -lm 

SOURCES := main.c \
		   timer1.c I2C.c  uart.c sensor.c seven.c  spi.c adc.c \
		   switches.c \
		   ft_itoa_dec.c ft_itoa_hex.c split_number.c \
		   mode0.c mode1.c mode2.c mode3.c mode4.c mode5.c mode6.c \
		   mode7.c mode8.c mode9.c mode10.c
BIN := $(SOURCES:.c=.bin)

DOTHEX := $(SOURCES:.c=.hex)

all : hex flash

hex: main.hex

main.hex: main.bin
	avr-objcopy -R eeprom -O ihex main.bin main.hex

main.bin: $(SOURCES) ATmega.h
	$(CC) $(CFLAGS) $(SOURCES) -o main.bin

flash:
	@killall screen 2> /dev/null || true
	avrdude -c arduino -b 115200 -p atmega328p -P /dev/ttyUSB0 -U flash:w:main.hex

debug: all
	gnome-terminal -- screen /dev/ttyUSB0 115200

clean:
	rm -f main.bin main.hex

.PHONY: all clean flash hex
