///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// emisorArdu.cpp
//
// Programa para Arduino que envía por el laser la cadena en Morse
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <ticcommardu.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <uart.h>
#include <arducodif.h>

int main(void){

    // Inicialización del puerto UART con la velocidad
    //  en baudios del puerto, y la velocidad del procesador
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Activación de las interrupciones hardware para
    //  control del puerto serie
    sei();

	initLaserEmitter(); // Iniciamos el láser

	while(1){

        char data[100] = "";

        arduReceiveUSB(data);

        unsigned int length = strlen(data);

        char cad_decodif[100] = {0};
        char codificado[100];
        unsigned char utiles[100];

        codificador(data, length, codificado, utiles);

        //decodificador(codificado, utiles, length, cad_decodif);

        //cad_decodif[length] = '\0';


        
        arduSendUSB("OK");



        // Enviamos: ...
        sendLaserBit(LASER_DOT);
        sendLaserBit(LASER_DOT);
        sendLaserBit(LASER_DOT);
        sendLaserBit(LASER_NONE);

        // Enviamos --
        sendLaserBit(LASER_DASH);
        sendLaserBit(LASER_DASH);
        sendLaserBit(LASER_NONE);

        // Enviamos: ...
        sendLaserBit(LASER_DOT);
        sendLaserBit(LASER_DOT);
        sendLaserBit(LASER_DOT);
        sendLaserBit(LASER_NONE);






	}

    return 0;

}
