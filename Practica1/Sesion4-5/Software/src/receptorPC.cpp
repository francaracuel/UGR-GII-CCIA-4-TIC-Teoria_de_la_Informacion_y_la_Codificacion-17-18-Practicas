///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// receptorPC.cpp
//
// Programa receptor para el PC. Mostrará los datos que llegan del fotorreceptor
//
////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <ticcommpc.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <signal.h>

using namespace std;

// Puerto de comunicaciones con arduino
#define USBPORT0 "/dev/ttyACM0"
#define USBPORT1 "/dev/ttyACM1"

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

// Programa principal
int main(int argc, char *argv[]){

    int port = 0;

    // Se lee el argumento recibido para cambiar el puerto del Arduino
    if(argc == 2 && atoi(argv[1]) == 1){
        port = 1;
    }

    // Descriptor de fichero del puerto USB
    int fd;

    // Buffer de salida. Tamaño máximo de 128 caracteres.
    char buf[129];

    // Inicializamos puerto
    if(port == 0){
      fd = InicializarUSB(USBPORT0);
    } else{
      fd = InicializarUSB(USBPORT1);
    }

    if(fd==-1){

        if(port == 0){
            cout << "Error inicializando puerto " << USBPORT0 << endl;
        } else{
            cout << "Error inicializando puerto " << USBPORT1 << endl;
        }

        return 0;

    }

    cout << "Comenzando a leer...\n" << endl;

    signal(SIGINT, intHandler);

    // Bucle principal
    while (keepRunning){

        // Se leen datos del USB
        if(receiveUSB(fd, buf)){

            cout << "Mensaje recibido: " << buf << endl;

        } else{

            cout << "\tError recibiendo datos\n\n";
            CerrarUSB(fd);
            return 0;

        }

    }

    // Se cierra el puerto USB
    CerrarUSB(fd);
    return 0;

}
