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

emisorArdu: emisorArducpp uartcpp
	@echo Generando binario Arduino emisor...
	avr-gcc -mmcu=atmega328p obj/ticcommardu.o obj/uart.o obj/emisorArdu.o -o obj/emisorArdu.bin
	@echo Generando HEX Arduino...
	avr-objcopy -O ihex -R .eeprom obj/emisorArdu.bin hex/emisorArdu.hex
	@echo emisorArdu compilado. Ejecute make sendEmisor para enviarlo a la plataforma Arduino.

receptorArdu: ticcommarducpp uartcpp receptorArducpp
	@echo Generado binario Arduino...
	avr-gcc -mmcu=atmega328p obj/ticcommardu.o obj/uart.o obj/receptorArdu.o -o obj/receptorArdu.bin
	@echo Generando HEX Arduino receptor...
	avr-objcopy -O ihex -R .eeprom obj/receptorArdu.bin hex/receptorArdu.hex
	@echo receptorArdu compilado. Ejecute make sendReceptor para enviarlo a la plataforma Arduino.

emisorArducpp:
	@echo Compilando emisorArdu receptor...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/emisorArdu.o src/emisorArdu.cpp -Iinclude

receptorArducpp:
	@echo Compilando receptorArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/receptorArdu.o src/receptorArdu.cpp -Iinclude

ticcommarducpp:
	@echo Compilando TICCommArdu...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/ticcommardu.o src/ticcommardu.cpp -Iinclude

uartcpp:
	@echo Compilando biblioteca UART...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/uart.o src/uart.cpp -Iinclude

sendEmisor:
	@echo Enviando emisorArdu a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:hex/emisorArdu.hex

sendReceptor:
	@echo Eviando receptorArdu a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:hex/receptorArdu.hex


