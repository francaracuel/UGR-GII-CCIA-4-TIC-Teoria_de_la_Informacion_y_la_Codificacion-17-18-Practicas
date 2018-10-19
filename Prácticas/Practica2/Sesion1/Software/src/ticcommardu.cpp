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

    // Asumimos que está en el pin 12 de Arduino
    DDRB |= _BV(DDB4);

    // Ponemos salida a baja
    PORTB &= ~_BV(DDB4);
}

void sendLaserBit(const unsigned char what) {

    // Ponemos salida a alta si hay que enviar ráfaga
    if (what != LASER_NONE)
        PORTB |= _BV(DDB4);

    // Esperamos el tiempo de ciclo
    if (what != LASER_DASH)
        _delay_ms(UMBRAL_U);
    else
        _delay_ms(2*UMBRAL_U);

    // Ponemos salida a baja
    PORTB &= ~_BV(DDB4);

    // Y esperamos un ciclo
    if (what != LASER_NONE)
        _delay_ms(UMBRAL_U);

}

void sendLaserBit2(const unsigned char what) {

    // Ponemos salida a alta si hay que enviar un 1
    if (what == LASER_HIGH)
        PORTB |= _BV(DDB4);
    else  // Ponemos a baja si se envia un 0
        PORTB &= ~_BV(DDB4);

    // Esperamos el tiempo de ciclo
    _delay_ms(UMBRAL_U);
}

void initLaserReceiver() {

    // Asumimos que está en el pin 8 de Arduino
    DDRB &= ~_BV(DDB0);
}

void recvLaserBit(unsigned char & what) {

    // Contador de veces que se detecta voltaje bajo y alto
    unsigned char cBajo = 0;
    unsigned char cAlto = 0;

    // Dato a medir
    unsigned char dato;

    // Inicialmente suponemos que está en bajo
    // Comprobamos si es mensaje LASER_NONE
    do {

        // Asumimos que está en el PIN 8
        dato = PINB & 0x01;

        if (dato > 0)
            cAlto++;
        else
            cBajo++;

        if (cBajo > 3){
            what = LASER_NONE;
            return;
        }

        // Esperamos al siguiente muestreo
        _delay_ms(SAMPLE_PERIOD);

    } while (dato ==0);

    // Si se llega aquí, está llegando una ráfaga
    // Se comprobación si es ráfaga corta o larga
    do{

        // Se asume que está en el  PIN 8
        dato = PINB & 0x01;

        if(dato>0)
            cAlto++;

        // Se espera al siguiente muestreo
        _delay_ms(SAMPLE_PERIOD);

    } while(dato > 0);

    // Si se ha muestreado más de 3 veces lo mismo, entonces es raya
    if(cAlto>3)
        what = LASER_DASH;

    // Si no, es un punto
    else
        what = LASER_DOT;

}

void recvLaserBit2(unsigned char & what) {

    // Contador de veces que se detecta voltaje bajo y alto
    unsigned char cBajo = 0;
    unsigned char cAlto = 0;

    // Tiempo midiendo
    unsigned char tiempo = 0;

    // Dato a medir
    unsigned char dato;

    // Pasamos un ciclo midiendo

    while (tiempo < UMBRAL_U){

        // Asumimos que está en el PIN 8
        dato = PINB & 0x01;

        if (dato>0)
            cAlto++;
        else
            cBajo++;

        // Esperamos el tiempo de muestreo
        _delay_ms(SAMPLE_PERIOD);

        // Aumentamos el tiempo que hemos estado en la función
        tiempo += SAMPLE_PERIOD;
    }

    // Si hemos muestreado más altas que bajas, devolvemos LASER_HIGH
    if (cAlto > cBajo)
        what = LASER_HIGH;
    else    // En otro caso, devolvemos LASER_LOW
        what = LASER_LOW;
}
