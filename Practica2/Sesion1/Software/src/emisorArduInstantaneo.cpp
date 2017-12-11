///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// emisorArdu.cpp
//
// Programa para Arduino que envía por el láser la cadena en Morse
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

        // Se recibe el texto del emirsorPC
        arduReceiveUSB(data);

        // Se guarda la longitud de la cadena
        unsigned int length = strlen(data);

        // Se crea el vector que contendrá la cadena codificada
        char encoded[100];

        // Se guarda el número de bits válidos por cada Byte
        unsigned char used[100];

        codificador(data, length, encoded, used);

        //arduSendUSB(data);
        //decodificador(encoded, used, length, data);
        //arduSendUSB(data);
        //decodificador(codificado, utiles, length, cad_decodif);

        //cad_decodif[length] = '\0';

        // Se recorre la cadena recibida
        for(unsigned int i=0; i<length; i++){

            // Se recupera el Byte codificado y cuando comienza la codificación
            char enc = encoded[i];
            unsigned int us = used[i];

            // Se recorren tantos bits como son utilizados
            for (int j = 0 ; j != us ; j++) {

                // Se comprueba si es un 0 o un 1. Si es un 0 se envía el láser
                // corto. Si es 1 se envía el láser largo.
                if((enc & (1 << j)) == 0){
                    sendLaserBit2(LASER_HIGH);
                } else{
                    sendLaserBit2(LASER_LOW);
                }

            }

            // Cuando termina de enviarse una letra no se envía nada
            //sendLaserBit(LASER_NONE);

        }

        // Cuando se termina de enviar la palabra no se envía nada
       // sendLaserBit(LASER_NONE);

        // Cuando se ha terminado de enviar la palabra se envía OK
        arduSendUSB("OK");

	}

    return 0;

}
