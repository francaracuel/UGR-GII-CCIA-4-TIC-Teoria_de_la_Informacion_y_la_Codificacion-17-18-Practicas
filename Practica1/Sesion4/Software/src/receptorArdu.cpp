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
    
    char cadena[101];
    unsigned int n=0;
    
    // Inicialización del puerto UART con la velocidad en baudios del puerto
    // y la velocidad del procesador
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    
    // Activación de las interrupciones hardware para control del puerto serie
    sei();
    
    // Inicialización del fotorreceptor
    initLaserReceiver();
    
    // Bucle infinito
    while(1){
        
        n = 0;
        
        // Se rellena el buffer
        for(int i=0; i<1000; i++){
            
            // Se recibe el dato
            recvLaserBit(dato);
            
            // Si es ráfaga corta, incluimos en el buffer un 0
            if(dato == LASER_DOT)
                cadena[n] = '0';
            
            // Si es ráfaga larga, incluimos en el buffer un 1
            else if(dato == LASER_DASH)
                cadena[n] = '1';
            
            // Si no se recibe nada, se incluye en el buffer un ?
            else
                cadena[n] = '?';
            
            // Se pasa al siguiente carácter en cadena
            n++;
            
        }
        
        // Se envía el mensaje al PC
        cadena[n] = '\0';
        arduSendUSB(cadena);
        
    }
    
    return 0;
    
}