///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// receptorArdu.cpp
//
// Programa para Arduino que recibe la señal del laser
//
////////////////////////////////////////////////////////////////////////////////

#include <ticcommardu.h>
#include <arducodif.h>
#include <avr/interrupt.h>
#include <uart.h>

// Programa principal
int main(void){

    // data a leer desde Arduino
    unsigned char data;

    // Buffers
    char laser[100] = {'A'};
    char decode[100] = {'A'};

    unsigned char used[100];

    // Inicialización del puerto UART con la velocidad en baudios del puerto
    // y la velocidad del procesador
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Activación de las interrupciones hardware para control del puerto serie
    sei();

    // Inicialización del fotorreceptor
    initLaserReceiver();

    // Estado - Recibiendo o espera
    bool receiving = false;

    // LASER_NONE recibidos
    int numLaserNone = 0;

    // Letra que se va decodificando cada vez
    char character = 0b00000000;

    // Contador de los bits utilizados por cada letra
    int us = 0;

    // Contador para la cantidad de letras que se leen
    unsigned int i = 0;

    // Bucle infinito
    while(1){

        // Se comprueba si está en el estado de espera
        if (!receiving){

            recvLaserBit(data);

            // Cuando no lea un LASER_NONE cambia de estado a "recibiendo"
            if (data != LASER_NONE){

                receiving = true;

            }

        }

        // Solo entra si está en estado recibiendo
        if (receiving){

            // El data es un punto
            if (data == LASER_DOT){

                us++;
                numLaserNone = 0;

            // El data es una raya
            }else if (data == LASER_DASH){

                // Se pone un 1 en la posición que le corresponde
                character ^= (1 << us);

                us++;
                numLaserNone = 0;

            // El data es nada
            }else{

                // Para controlar la cantidad de LASER_NONE que se recibe se
                // aumenta el contador
                numLaserNone++;

            }

            // Si lee un LASER_NONE es que se ha terminado la letra
            if (numLaserNone == 1){

                // Se guarda el carácter que se ha leído
                laser[i] = character;

                // Se guarda cuantos bits han sido necesarios para esta letra
                used[i] = us;

                // Se resetea el carácter que se está leyendo
                character = 0b00000000;

                // Se reinicializa el contador de bits de cada letra
                us = 0;

                // Se aumenta la posición de la siguiente letra
                i++;

                arduSendUSB("Fin de letra");

            // Dos LASER_NONE es que ha terminado de leerse el texto
            } else if(numLaserNone == 2){

                // Cuando ya está la cadena completa, se decodifica
                decodificador(laser, used,  i, decode);

                // Se concatena \0 para que se visualice correctamente
                decode[i] = '\0';

                // Se inicializan las variables necesarias
                receiving = false;
                numLaserNone = 0;
                i = 0;

                // Se manda al pc la cadena decodificada
                arduSendUSB(decode);

                arduSendUSB("Fin de texto");

            }

            // Se lee el láser para el siguiente ciclo
            recvLaserBit(data);

        }

    }

    return 0;

}
