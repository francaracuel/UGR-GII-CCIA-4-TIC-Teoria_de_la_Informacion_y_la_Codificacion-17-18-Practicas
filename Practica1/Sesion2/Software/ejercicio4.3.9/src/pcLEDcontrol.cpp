///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// pcLedcontrol.cpp
//
// Programa para PC que envía datos a Arduino
//
////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <ticcommpc.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>

using namespace std;

// Puerto de comunicaciones con arduino

/* MODIFICAR EL PUERTO CON AQUEL DONDE SE VAYA A CONECTAR ARDUINO */
#define USBPORT "/dev/ttyACM0"

int main(int argc, char *argv[]) {

    // Se comprueba si se ha recibido la orden por parámetro
    if (argc != 2) {

        cout << "\nError al ejecutar el programa...";
        cout << "\nUso: " << argv[0] << " [On|Off]\n\n";

        exit(-1);

    }

    // Descriptor de puerto del puerto USB
    int fd;
    
    // Buffer de salida. Tamaño máximo de 128 caracteres
    char *buf = argv[1];
    //char buf[129];
        
    // Número de datos en el buffer
    int ndata;
    
    int aux;

    // Inicializamos puerto

    fd = InicializarUSB(USBPORT);

    if (fd == -1) {
        cout << "Error inicializando puerto " << USBPORT << endl;
        return 0;
    }

    // Bucle hasta que salgamos (cuando no introduzcamos nada)
    //do {

        //cout << "Escriba algo para enviar a Arduino: ";
        //cin.getline(buf, 128);

        ndata = strlen(buf); //Tamaño del buffer de salida

        if (ndata > 0) {
            
            aux = write(fd, buf, ndata);
            
            tcflush(fd, TCIFLUSH);
            
            cout << "\nBytes enviados " << aux << "/" << ndata << endl;

            // Comprobamos errores en el envío
            if (aux < ndata) {
                
                cout << "Error, en el buffer tiene " << ndata << " bytes pero se enviaron " << aux << endl;
                ndata = 0;
                
            }

            // Si se envió algun dato, esperamos respuesta de Arduino
            if (aux > 0) {
                
                //aux = receiveUSB(fd, buf);
                aux = read(fd, buf, 128);
                
                if (aux > 0)
                    cout << "\nMensaje: " << buf << endl;
                else
                    cout << "ERROR RECIBIENDO DATOS\n";
                
            }
            
        }

    // Se sale si no enviamos ningún caracter
    //} while (ndata > 0);

    // Cerramos el puerto USB
    CerrarUSB(fd);

    cout << "\nFin del programa.\n\n";

    return 0;

}
