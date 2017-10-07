///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// arduLEDcontrol.cpp
//
// Programa para Arduino que recibe una cadena ON/OFF y enciende o apaga el led
//
////////////////////////////////////////////////////////////////////////////////

// Ciclo de reloj del procesador: 16MHz
#define F_CPU 16000000UL

// Velocidad (en baudios) de las comunicaciones serie
#define UART_BAUD_RATE 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <uart.h>
#include <util/delay.h>

#include "ticcommardu.cpp"

#define BLINK_DELAY_MS 1000

int main(void) {

    // Se establece como entrada el pin 12
    DDRB |= 0b00010000;

    // Inicialización del puerto UART con la velocidad
    //  en baudios del puerto, y la velocidad del procesador
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Activación de las interrupciones hardware para
    //  control del puerto serie
    sei();

    bool light = true;

    while (1) {

        char data[128] = "";

        arduReceiveUSB(data);

        if (strcmp(data, "On") == 0) {

            light = true;
            
            arduSendUSB("Led encendido");
            
        } else if (strcmp(data, "Off") == 0) {

            light = false;
            
            arduSendUSB("Led apagado");

        } else{
            
            arduSendUSB("No entiendo la orden");
            
        }

        if (light) {

            // Se manda la señal de voltaje alto al pin 12 del puerto B
            PORTB |= 0b00010000;
            _delay_ms(BLINK_DELAY_MS);

        } else {

            // Se manda la señal de voltaje bajo al pin 0 del puerto B
            PORTB &= 0b00000000;
            _delay_ms(BLINK_DELAY_MS);

        }

    }

    return 0;

}
