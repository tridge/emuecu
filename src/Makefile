PRG            = ecu
OBJ            = ecu.o uart.o timers.o rpm.o injection.o inputs.o twimaster.c bme280.c max6675.c config.c log.c
HDR            = ecu.h config.h emu_types.h uart.h timers.h rpm.h injection.h inputs.h i2cmaster.h bme280.h bme280_defs.h max6675.h log.h
MCU_TARGET     = atmega328p
OPTIMIZE       = -Os

AVRDUDE_PORT   = /dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A602QP81-if00-port0
#AVRDUDE_PORT   = /dev/serial/by-id/usb-FTDI_FT232R_USB_UART_A602K6GX-if00-port0
#AVRDUDE_PORT   = /dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0

AVRDUDE_DEVICE = arduino

DEFS           =-I/usr/lib/avr/include
LIBS           =-L/usr/lib/avr/lib/avr5 -L/usr/lib/avr/lib

# You should not have to change anything below here.

CC             = avr-gcc

# Override is only needed by avr-lib build system.

override CFLAGS        = -g -std=c99 -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS       = -Wl,-Map,$(PRG).map,-u,vfprintf -lprintf_flt -lm

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

# rule that makes all .c depend all .h
%.o: %.c $(HDR)
	$(CC) -c $(CFLAGS) -o $@ $< $(LIBS)

all: $(PRG).elf lst text eeprom

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak 
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

load: $(PRG).hex
	stty -F $(AVRDUDE_PORT) hupcl
	avrdude -vv -b 57600 -p $(MCU_TARGET) -c $(AVRDUDE_DEVICE) -P $(AVRDUDE_PORT) -Uflash:w:$(PRG).hex

lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

eeprom: ehex ebin esrec

ehex:  $(PRG)_eeprom.hex
ebin:  $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec

%_eeprom.hex: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

%_eeprom.srec: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@

%_eeprom.bin: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@

EXTRA_CLEAN_FILES       = *.hex *.bin *.srec


