################################################################################
##
## Makefile para la creación de programas y envío a Arduino
##
## Juan Manuel Fajardo Sarmiento
## Francisco Javier Caracuel Beltrán
##
## TIC - Teoría de la Información y la Codificación - CCIA
##
## ETSIIT - UGR
##
## Curso 2017-2018
##
################################################################################

MAC = /dev/tty.usbmodem1411
LINUX1 = /dev/ttyACM0
LINUX2 = /dev/ttyACM1

#COMMPORT = $(MAC)
COMMPORT = $(LINUX1)
#COMMPORT = $(LINUX2)

EXEC = main
SEND = send
CPP = $(EXEC).cpp
OBJ = $(EXEC).o
BIN = $(EXEC).bin
HEX = $(EXEC).hex

all: $(EXEC) $(SEND)

$(EXEC):
	@echo Compilando $(EXEC)...
	@avr-gcc -Os -mmcu=atmega328p -c -o $(OBJ) $(CPP)
	@avr-gcc -mmcu=atmega328p $(OBJ) -o $(BIN)
	@avr-objcopy -O ihex -R .eeprom $(BIN) $(HEX)
	@echo Programa $(EXEC) compilado. Ejecute make $(SEND) para enviarlo a Arduino

$(SEND):
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:$(HEX)

clean:
	rm -f -r *~
	rm -f -r *.o
	rm -f -r *.hex
	rm -f -r *.bin
