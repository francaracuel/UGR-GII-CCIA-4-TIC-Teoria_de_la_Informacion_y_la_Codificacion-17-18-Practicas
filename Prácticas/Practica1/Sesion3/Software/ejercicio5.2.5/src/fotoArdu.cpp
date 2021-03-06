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
#include <avr/interrupt.h>
#include <uart.h>
#include <util/delay.h>

// Tiempo a dormir en microsegundos
#define DELAY_US 125

// Programa principal
int main(void){

    // Dato a leer desde el sensor
    unsigned char data;

    // Inicialización del puerto UART con la velocidad en baudios del puerto
    // y la velocidad del procesador
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Activación de las interrupciones hardware para control del puerto serie
    sei();

    while (1) {

        // Cogemos qué hay en el PIN 10 como entrada
        data = PINB & 0b00000100;

        if (data > 0) {

            arduSendUSB("1");

        } else if (data == 0 ) {

            arduSendUSB("0");

        }

        // Se duerme
        _delay_us(DELAY_US);

    }

    return 0;

}
