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
#include <string.h>

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
    
    unsigned int c;
    
    unsigned int n = 0;
    
    char data[129] = "";
    
    char dataOn[129] = "Led encendido\0";
    char dataOff[129] = "Led apagado\0";
    char dataNA[129] = "No entiendo la orden\0";

    while(1){
        
        do{
        
            // Se recoge el byte desde el puerto UART
            c = uart_getc();

            // Flag sin datos activado. Se duerme
            if (c & UART_NO_DATA) {
                _delay_ms(1);

                // Error de recepción de la trama de datos. Se envía el mensaje
            } else if (c & UART_FRAME_ERROR) {

                uart_puts_P("Error recibiendo trama.\n");

                // Error de recepción de dato más rápido de lo que se pudo leer el
                //anterior
            } else if (c & UART_OVERRUN_ERROR) {

                uart_puts_P("Error: La interrupción no pudo leer el dato antes de recibir el siguiente.\n");

                // Error de recepción: Buffer lleno. No estamos leyendo tan rápido como
                // nos envían
            } else if (c & UART_BUFFER_OVERFLOW) {

                uart_puts_P("Error: El buffer está lleno. No se puede leer tan rápido como se envía\n");

                // Todo ok. Se responde con el mismo carácter
            } else {

                data[n] = (unsigned char)c;
                n++;
                //uart_putc((unsigned char)c);

            }
            
        } while(c!='\0');
              
        // Se comprueba qué se debe hacer con el led
        if (strcmp(data, "On") == 0) {

            light = true;
            
            strcpy(data, dataOn);
            
        } else if (strcmp(data, "Off") == 0) {

            light = false;
            
            strcpy(data, dataOff);

        } else{
            
            strcpy(data, dataNA);
            
        }

        if (light) {

            // Se manda la señal de voltaje alto al pin 12 del puerto B
            PORTB |= 0b00010000;

        } else {

            // Se manda la señal de voltaje bajo al pin 0 del puerto B
            PORTB &= 0b11101111;        

        }
        
        unsigned int length = strlen(data);

        n = 0;

        // Se recorre la cadena completa
        while (n <= length) {

            // Se envía el carácter
            uart_putc(data[n]);

            n++;

        }

    }

    return 0;

}
