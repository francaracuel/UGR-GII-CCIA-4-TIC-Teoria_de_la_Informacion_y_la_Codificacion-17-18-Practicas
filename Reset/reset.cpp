///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// Reset - Resetea los pines de la placa a unos valores dados
//
////////////////////////////////////////////////////////////////////////////////

// Se utiliza para el cálculo de ms en _delay_ms
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void){

    // Se pone como salida el pin 12
    DDRB |= 0b00010000;

    // Se pone como entrada el pin 8
    DDRB &= 0b111111110;

}
