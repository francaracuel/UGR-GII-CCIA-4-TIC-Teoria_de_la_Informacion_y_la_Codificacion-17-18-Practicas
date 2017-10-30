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

// Velocidad (en baudios) de las comunicaciones serie
#define UART_BAUD_RATE 9600

#include <ticcommardu.h>
#include <avr/interrupt.h>
#include <uart.h>

// Programa principal
int main(void){
    
    // Dato a leer desde Arduino
    unsigned char dato;

    // Buffers
    char laser[100];
    char decodificado[100];
    
    char cadena[100];
    unsigned int n=0;
    
    // Inicialización del puerto UART con la velocidad en baudios del puerto
    // y la velocidad del procesador
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    
    // Activación de las interrupciones hardware para control del puerto serie
    sei();
    
    // Inicialización del fotorreceptor
    initLaserReceiver();

    // Estado - Recibiendo o espera
    bool recibiendo = false; 

    // LASER_NONE recibidos
    int num_laser_none = 0;

    int utiles = 0;

    // Bucle infinito
    while(1){
        
        if (recibiendo == false){
            recvLaserBit(dato);

            if (dato != LASER_NONE)
                recibiendo = true;
        }

        if (recibiendo == true){

            // Se recibe el dato
            recvLaserBit(dato);

            
            if (dato == LASER_DOT){
                //bit 0
                utiles++;
                num_laser_none = 0;
            }
            else if (dato == LASER_DASH){
                // bit 1
                utiles++;
                num_laser_none = 0;
            }
            else if (dato == LASER_NONE)
                n++;
                num_laser_none++;



            if (num_laser_none == 2)
                recibiendo = false;
                decodificador(laser,utiles,n,decodificado);
                arduSendUSB(decodificado);
                n = 0;
                utiles = 0;

        }

    }
    
    return 0;
    
}