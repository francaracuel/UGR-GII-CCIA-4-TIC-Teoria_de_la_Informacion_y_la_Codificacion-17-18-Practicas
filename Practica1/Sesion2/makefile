
# Puerto de comunicaciones donde se encuentra Arduino.
COMMPORT = /dev/ttyACM0


arduecho: arduechocpp uartcpp
	@echo Generando binario Arduino...
	avr-gcc -mmcu=atmega328p obj/arduecho.o obj/uart.o -o obj/arduecho.bin
	@echo Generando HEX Arduino...
	avr-objcopy -O ihex -R .eeprom obj/arduecho.bin hex/arduecho.hex
	@echo Arduecho compilado. Ejecute make send para enviarlo a la plataforma Arduino.

arduechocpp:
	@echo Compilando arduecho...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/arduecho.o src/arduecho.cpp -Iinclude

uartcpp:
	@echo Compilando biblioteca UART...
	avr-gcc -Os -mmcu=atmega328p -c -o obj/uart.o src/uart.cpp -Iinclude


send:
	@echo Enviando arduecho a Arduino
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P $(COMMPORT) -b 115200 -U flash:w:hex/arduecho.hex


pcecho: pcechocpp ticcommpccpp
	@echo Generando fichero binario pcecho...
	g++ -o bin/pcecho obj/pcecho.o obj/ticcommpc.o

pcechocpp:
	@echo Compilando PCECHO...
	g++ -c -o obj/pcecho.o src/pcecho.cpp -Iinclude


ticcommpccpp:
	@echo Compilando fuentes de biblioteca TICCommPC...
	g++ -c -o obj/ticcommpc.o src/ticcommpc.cpp -Iinclude


