///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// ticcomardu.cpp
//
// Biblioteca para el manejo de datos con Arduino
//
////////////////////////////////////////////////////////////////////////////////

#include <ticcommardu.h>
#include <uart.h>
#include <string.h>
#include <util/delay.h>

bool arduSendUSB(const char *data) {

    // Se obtiene el tamaño de la cadena
    unsigned int length = strlen(data);

    unsigned int n = 0;

    // Se recorre la cadena completa
    while (n <= length) {

        // Se envía el carácter
        uart_putc(data[n]);

        n++;

    }

    //uart_puts(data);

}

bool arduReceiveUSB(char *data) {

    bool error = false;

    unsigned int n = 0;

    // Se recoge el byte desde el puerto UART
    char c = uart_getc();

    // Se lee hasta que sea el fin del fichero
    while (c != '\0') {

        // Flag sin datos activado. Se duerme
        if (c & UART_NO_DATA) {
            _delay_ms(1);

            // Error de recepción de la trama de datos. Se envía el mensaje
        } else if (c & UART_FRAME_ERROR) {

            error = true;

            // Error de recepción de dato más rápido de lo que se pudo leer el
            //anterior
        } else if (c & UART_OVERRUN_ERROR) {

            error = true;

            // Error de recepción: Buffer lleno. No estamos leyendo tan rápido como
            // nos envían
        } else if (c & UART_BUFFER_OVERFLOW) {

            error = true;

            // Todo ok. Se responde con el mismo carácter
        } else {

            data[n] = c;

            n++;

        }

        // Se recoge el byte desde el puerto UART
        c = uart_getc();

    }

    if (!error) {
        data[n] = '\0';
    }

    return !error;

}

bool arduSendByteUSB(unsigned char data) {

    // Se envía el carácter
    uart_putc(data);

    return true;

}

bool arduReceiveByteUSB(unsigned char &data) {

    bool error = false;

    // Se recoge el byte desde el puerto UART
    char c = uart_getc();

    // Flag sin datos activado. Se duerme
    if (c & UART_NO_DATA) {

        _delay_ms(1);

        error = true;

        // Error de recepción de la trama de datos. Se envía el mensaje
    } else if (c & UART_FRAME_ERROR) {

        error = true;

        // Error de recepción de dato más rápido de lo que se pudo leer el
        //anterior
    } else if (c & UART_OVERRUN_ERROR) {

        error = true;

        // Error de recepción: Buffer lleno. No estamos leyendo tan rápido como
        // nos envían
    } else if (c & UART_BUFFER_OVERFLOW) {

        error = true;

        // Todo ok. Se responde con el mismo carácter
    } else {

        data = c;

    }

    return !error;

}

void initLaserEmitter() {

    /* COMPLETAR CODIGO */
}

void sendLaserBit(const unsigned char what) {

    /* COMPLETAR CODIGO */
}

void initLaserReceiver() {

    /* COMPLETAR CODIGO */
}

void recvLaserBit(unsigned char & what) {

    /* COMPLETAR CODIGO */
}
