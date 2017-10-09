#include <ticcommardu.h>
#include <util/delay.y>

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