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
LINUX1 = /dev/ttyACM0
LINUX2 = /dev/ttyACM1

COMMPORT = $(MAC)
COMMPORT = $(LINUX1)
#COMMPORT = $(LINUX2)

arduLEDcontrol: arduLEDcontrolcpp uartcpp
	@echo Generando binario Arduino...
	avr-gcc -mmcu=atmega328p obj/arduLEDcontrol.o obj/uart.o -o obj/arduLEDcontrol.bin
	@echo Generando HEX Arduino...
	avr-objcopy -O ihex -R .eeprom obj/arduLEDcontrol.bin hex/arduLEDcontrol.hex
	@echo Arduecho compilado. Ejecute make send para enviarlo a la plataforma Arduino.

arduLEDcontrolcpp:
	@echo Compilando arduLEDcontrol...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/arduLEDcontrol.o src/arduLEDcontrol.cpp -Iinclude

uartcpp:
	@echo Compilando biblioteca UART...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/uart.o src/uart.cpp -Iinclude


send:
	@echo Enviando arduLEDcontrol a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:hex/arduLEDcontrol.hex


pcLEDcontrol: pcLEDcontrolcpp ticcommpccpp
	@echo Generando fichero binario pcLEDcontrol...
	g++ -o bin/pcLEDcontrol obj/pcLEDcontrol.o obj/ticcommpc.o

pcLEDcontrolcpp:
	@echo Compilando PCECHO...
	g++ -c -o obj/pcLEDcontrol.o src/pcLEDcontrol.cpp -Iinclude

ticcommpccpp:
	@echo Compilando fuentes de biblioteca TICCommPC...
	g++ -c -o obj/ticcommpc.o src/ticcommpc.cpp -Iinclude
