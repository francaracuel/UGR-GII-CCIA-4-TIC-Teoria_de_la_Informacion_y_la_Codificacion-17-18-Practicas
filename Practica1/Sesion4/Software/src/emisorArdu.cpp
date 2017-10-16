///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// emisorArdu.cpp
//
// Programa para Arduino que envía por el laser la cadena en Morse
//
////////////////////////////////////////////////////////////////////////////////

#include <ticcommardu.h>
#include <util/delay.h>
#include <avr/io.h>

int main(void){
    
	initLaserEmitter(); // Iniciamos el láser

	while(1){
            
            // Enviamos: ...
            sendLaserBit(LASER_DOT);
            sendLaserBit(LASER_DOT);
            sendLaserBit(LASER_DOT);
            sendLaserBit(LASER_NONE);

            // Enviamos --
            sendLaserBit(LASER_DASH);
            sendLaserBit(LASER_DASH);
            sendLaserBit(LASER_NONE);

            // Enviamos: ...
            sendLaserBit(LASER_DOT);
            sendLaserBit(LASER_DOT);
            sendLaserBit(LASER_DOT);
            sendLaserBit(LASER_NONE);

	}
    
    return 0;
    
}