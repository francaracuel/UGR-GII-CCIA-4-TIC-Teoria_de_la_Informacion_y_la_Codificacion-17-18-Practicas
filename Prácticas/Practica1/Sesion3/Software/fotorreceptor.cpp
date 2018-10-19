///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// fotorreceptor.cpp
//
// Programa que activa un led si el sensor detecta luz
//
////////////////////////////////////////////////////////////////////////////////

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

// Tiempo a dormir en microsegundos
#define DELAY_US 500

int main(void) {

    unsigned char dato; // Dato a leer desde el sensor
    bool currentLEDstate = false; // Estado actual del LED

    DDRB |= _BV(DDB4); // Pin 12 como salida
    DDRB &= ~_BV(DDB0); // Pin 8 como entrada

    // Comenzamos con el LED apagado
    PORTB &= ~_BV(PORTB4);
    currentLEDstate = false;

    while (1) {
        
        // Cogemos qué hay en el PIN 8 como entrada
        dato = PINB & 0x01;

        if (dato > 0 && !currentLEDstate) {
            PORTB |= _BV(PORTB4);
            currentLEDstate = true;
        } else if (dato == 0 && currentLEDstate) {
            PORTB &= ~_BV(PORTB4);
            currentLEDstate = false;
        }

        // Dormimos medio milisegundo
        _delay_us(DELAY_US);
    }

    return 0;

}