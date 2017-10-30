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

COMMPORT = $(MAC)
COMMPORT = $(LINUX0)
#COMMPORT = $(LINUX1)

COMMPORT2 = $(MAC)
COMMPORT2 = $(LINUX0)
COMMPORT2 = $(LINUX1)

all: emisorArdu receptorArdu emirsorPC receptorPC send

emisorArdu: ticcommarducpp arducodifcpp uartcpp emisorArducpp
	@echo Generando binario Arduino emisor...
	avr-gcc -mmcu=atmega328p obj/ticcommardu.o obj/arducodif.o obj/uart.o obj/emisorArdu.o -o obj/emisorArdu.bin
	@echo Generando HEX Arduino...
	avr-objcopy -O ihex -R .eeprom obj/emisorArdu.bin hex/emisorArdu.hex
	@echo emisorArdu compilado. Ejecute make sendEmisor para enviarlo a la plataforma Arduino.

receptorArdu: ticcommarducpp arducodifcpp uartcpp receptorArducpp
	@echo Generado binario Arduino...
	avr-gcc -mmcu=atmega328p obj/ticcommardu.o obj/arducodif.o obj/uart.o obj/receptorArdu.o -o obj/receptorArdu.bin
	@echo Generando HEX Arduino receptor...
	avr-objcopy -O ihex -R .eeprom obj/receptorArdu.bin hex/receptorArdu.hex
	@echo receptorArdu compilado. Ejecute make sendReceptor para enviarlo a la plataforma Arduino.

emisorArducpp:
	@echo Compilando emisorArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/emisorArdu.o src/emisorArdu.cpp -Iinclude

receptorArducpp:
	@echo Compilando receptorArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/receptorArdu.o src/receptorArdu.cpp -Iinclude

emirsorPC: emirsorPCcpp ticcommpccpp
	@echo Generando fichero binario emirsorPC...
	g++ -o bin/emisorPC obj/emirsorPC.o obj/ticcommpc.o

emirsorPCcpp:
	@echo Compilando emirsorPC...
	g++ -c -o obj/emirsorPC.o src/emisorPC.cpp -Iinclude

receptorPC: receptorpccpp ticcommpccpp
	@echo Generando fichero binario receptorPC...
	g++ -o bin/receptorPC obj/receptorPC.o obj/ticcommpc.o

receptorpccpp:
	@echo Compilando receptorPC...
	g++ -c -o obj/receptorPC.o src/receptorPC.cpp -Iinclude

ticcommarducpp:
	@echo Compilando TICCommArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/ticcommardu.o src/ticcommardu.cpp -Iinclude

ticcommpccpp:
	@echo Compilando fuentes de biblioteca TICCommPC...
	g++ -c -o obj/ticcommpc.o src/ticcommpc.cpp -Iinclude

arducodifcpp:
	@echo Compilando ArduCodif...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/arducodif.o src/arducodif.cpp -Iinclude

uartcpp:
	@echo Compilando biblioteca UART...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/uart.o src/uart.cpp -Iinclude

send: sendEmisor sendReceptor

sendEmisor:
	@echo Enviando emisorArdu a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:hex/emisorArdu.hex

sendReceptor:
	@echo Eviando receptorArdu a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT2) -b 115200 -U flash:w:hex/receptorArdu.hex
