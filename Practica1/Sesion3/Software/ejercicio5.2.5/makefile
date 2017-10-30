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

# Puerto de comunicaciones donde se encuentra Arduino.
MAC = /dev/tty.usbmodem1411
#LINUX0 = /dev/ttyACM0
#LINUX1 = /dev/ttyACM1
LINUX0 = /dev/ttyUSB0
LINUX1 = /dev/ttyACM1

#COMMPORT = $(MAC)
COMMPORT = $(LINUX0)
#COMMPORT = $(LINUX1)

#COMMPORT2 = $(MAC)
#COMMPORT2 = $(LINUX0)
COMMPORT2 = $(LINUX1)

SEND = send
SRC = src
OBJ = obj
BIN = bin
HEX = hex

CLEAN = clean

all: fotoArdu fotoPC $(SEND)

fotoArdu: ticcommarducpp uartcpp fotoArducpp
	@echo Generado binario Arduino...
	avr-gcc -mmcu=atmega328p $(OBJ)/ticcommardu.o $(OBJ)/uart.o $(OBJ)/fotoArdu.o -o $(BIN)/fotoArdu.bin
	@echo Generando HEX Arduino receptor...
	avr-objcopy -O ihex -R .eeprom $(BIN)/fotoArdu.bin $(HEX)/fotoArdu.hex
	@echo fotoArdu compilado. Ejecute make sendReceptor para enviarlo a la plataforma Arduino.

fotoArducpp:
	@echo Compilando fotoArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJ)/fotoArdu.o $(SRC)/fotoArdu.cpp -Iinclude

fotoPC: fotoPCcpp ticcommpccpp
	@echo Generando fichero binario fotoPC...
	g++ -o $(BIN)/fotoPC $(OBJ)/fotoPC.o $(OBJ)/ticcommpc.o

fotoPCcpp:
	@echo Compilando fotoPC...
	g++ -c -o $(OBJ)/fotoPC.o $(SRC)/fotoPC.cpp -Iinclude

ticcommarducpp:
	@echo Compilando TICCommArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJ)/ticcommardu.o $(SRC)/ticcommardu.cpp -Iinclude

ticcommpccpp:
	@echo Compilando fuentes de biblioteca TICCommPC...
	g++ -c -o $(OBJ)/ticcommpc.o $(SRC)/ticcommpc.cpp -Iinclude

uartcpp:
	@echo Compilando biblioteca UART...
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJ)/uart.o $(SRC)/uart.cpp -Iinclude

$(SEND): sendReceptor

sendReceptor:
	@echo Eviando fotoArdu a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:$(HEX)/fotoArdu.hex

$(CLEAN):
	@echo
	@echo Haciendo limpieza...
	rm -Rf $(OBJ)/* $(BIN)/* $(HEX)/*
	@echo Limpieza terminada
	@echo
