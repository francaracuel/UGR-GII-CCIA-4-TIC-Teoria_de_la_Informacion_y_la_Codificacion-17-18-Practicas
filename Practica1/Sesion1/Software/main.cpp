///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// Ejemplo 1 - Prueba de funcionamiento de led con Arduino
//
////////////////////////////////////////////////////////////////////////////////

// Se utiliza para el cálculo de ms en _delay_ms
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void) {

    // Pin 4 del puerto B del micro puesto como salida
    DDRB |= _BV(DDB4);

    while (1) {

        // Se manda la señal de voltaje alto al pin 4 del puerto B
        PORTB |= _BV(PORTB4);
        _delay_ms(BLINK_DELAY_MS);

        // Se manda la señal de voltaje bajo al pin 4 del puerto B
        PORTB &= ~_BV(PORTB4);
        _delay_ms(BLINK_DELAY_MS);

    }

}
