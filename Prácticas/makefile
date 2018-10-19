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

all: emisorArdu receptorArdu emirsorPC receptorPC $(SEND)

emisorArdu: ticcommarducpp arducodifcpp uartcpp emisorArducpp
	@echo Generando binario Arduino emisor...
	avr-gcc -mmcu=atmega328p $(OBJ)/ticcommardu.o $(OBJ)/arducodif.o $(OBJ)/uart.o $(OBJ)/emisorArdu.o -o $(BIN)/emisorArdu.bin
	@echo Generando HEX Arduino...
	avr-objcopy -O ihex -R .eeprom $(BIN)/emisorArdu.bin $(HEX)/emisorArdu.hex
	@echo emisorArdu compilado. Ejecute make sendEmisor para enviarlo a la plataforma Arduino.

receptorArdu: ticcommarducpp arducodifcpp uartcpp receptorArducpp
	@echo Generado binario Arduino...
	avr-gcc -mmcu=atmega328p $(OBJ)/ticcommardu.o $(OBJ)/arducodif.o $(OBJ)/uart.o $(OBJ)/receptorArdu.o -o $(BIN)/receptorArdu.bin
	@echo Generando HEX Arduino receptor...
	avr-objcopy -O ihex -R .eeprom $(BIN)/receptorArdu.bin $(HEX)/receptorArdu.hex
	@echo receptorArdu compilado. Ejecute make sendReceptor para enviarlo a la plataforma Arduino.

emisorArducpp:
	@echo Compilando emisorArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJ)/emisorArdu.o $(SRC)/emisorArdu.cpp -Iinclude

receptorArducpp:
	@echo Compilando receptorArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJ)/receptorArdu.o $(SRC)/receptorArdu.cpp -Iinclude

emirsorPC: emirsorPCcpp ticcommpccpp
	@echo Generando fichero binario emirsorPC...
	g++ -o $(BIN)/emisorPC $(OBJ)/emirsorPC.o $(OBJ)/ticcommpc.o

emirsorPCcpp:
	@echo Compilando emirsorPC...
	g++ -c -o $(OBJ)/emirsorPC.o $(SRC)/emisorPC.cpp -Iinclude

receptorPC: receptorpccpp ticcommpccpp
	@echo Generando fichero binario receptorPC...
	g++ -o $(BIN)/receptorPC $(OBJ)/receptorPC.o $(OBJ)/ticcommpc.o

receptorpccpp:
	@echo Compilando receptorPC...
	g++ -c -o $(OBJ)/receptorPC.o $(SRC)/receptorPC.cpp -Iinclude

ticcommarducpp:
	@echo Compilando TICCommArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJ)/ticcommardu.o $(SRC)/ticcommardu.cpp -Iinclude

ticcommpccpp:
	@echo Compilando fuentes de biblioteca TICCommPC...
	g++ -c -o $(OBJ)/ticcommpc.o $(SRC)/ticcommpc.cpp -Iinclude

arducodifcpp:
	@echo Compilando ArduCodif...
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJ)/arducodif.o $(SRC)/arducodif.cpp -Iinclude

uartcpp:
	@echo Compilando biblioteca UART...
	avr-gcc -Os -mmcu=atmega328p -c -o $(OBJ)/uart.o $(SRC)/uart.cpp -Iinclude

$(SEND): sendEmisor sendReceptor

sendEmisor:
	@echo Enviando emisorArdu a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:$(HEX)/emisorArdu.hex

sendReceptor:
	@echo Eviando receptorArdu a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT2) -b 115200 -U flash:w:$(HEX)/receptorArdu.hex

$(CLEAN):
	@echo
	@echo Haciendo limpieza...
	rm -Rf $(OBJ)/* $(BIN)/* $(HEX)/*
	@echo Limpieza terminada
	@echo

