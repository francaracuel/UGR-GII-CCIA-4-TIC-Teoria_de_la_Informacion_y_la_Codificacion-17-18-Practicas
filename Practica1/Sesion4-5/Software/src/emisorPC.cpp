///////////////////////////////////////////////////////////////////////////////
//
// Juan Manuel Fajardo Sarmiento
// Francisco Javier Caracuel Beltrán
//
// TIC - 2017/2018 - 4º - GII - CCIA
//
// emirsorPC.cpp
//
// Programa para PC que envía datos a Arduino
//
////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <ticcommpc.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <ctype.h>

using namespace std;

// Puerto de comunicaciones con arduino

/* MODIFICAR EL PUERTO CON AQUEL DONDE SE VAYA A CONECTAR ARDUINO */
//#define USBPORT0 "/dev/ttyACM0"
//#define USBPORT1 "/dev/ttyACM1"
//#define USBPORT0 "/dev/ttyUSB0"
//#define USBPORT1 "/dev/ttyUSB1"
#define USBPORT0 "/dev/tty.usbmodem1411"
#define USBPORT1 "/dev/tty.usbmodem1431"

int main(int argc, char *argv[]) {

    int port = 0;

    // Se lee el argumento recibido para cambiar el puerto del Arduino
    if(argc == 2 && atoi(argv[1]) == 1){
      port = 1;
    }

    // Descriptor de puerto del puerto USB
    int fd;

    // Buffer de salida. Tamaño máximo de 100 caracteres
    char buf[100];

    // Número de datos en el buffer
    int ndata;

    int aux;
    
    // Inicializamos puerto
    if(port == 0){
      fd = InicializarUSB(USBPORT0);
    } else{
      fd = InicializarUSB(USBPORT1);
    }

    if (fd == -1) {

        if(port == 0){
            cout << "Error inicializando puerto " << USBPORT0 << endl;
        } else{
            cout << "Error inicializando puerto " << USBPORT1 << endl;
        }

        return 0;

    }

    // Bucle hasta que salgamos (cuando no introduzcamos nada)
    do{

        cout << "Escriba algo para enviar a Arduino: ";
        cin.getline(buf, 100);

        // Tamaño del buffer de salida
        ndata = strlen(buf);

        // Se comprueba si los carácteres recibidos son correctos
        int i = 0;

        while(i<ndata){

            // Si el carácter está en minúscula, se convierte a mayúscula
            if(buf[i] >= 'a' && buf[i] <= 'z'){
                buf[i] = toupper(buf[i]);
            }

            // Si es algún carácter inválido se termina el programa
            if(!((buf[i] >= 'A' && buf[i] <= 'Z') || buf[i] == '.' ||
                buf[i] == ',' || buf[i] == ';'  || buf[i] == ' ' )){

                cout << "Error al recibir caracteres inválidos" << endl;
                ndata = 0;
                aux = 0;

            }

            i++;

        }

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

                do{

                    aux = receiveUSB(fd, buf);

                    //cout << "\nMensaje: " << buf << endl;

                }while(buf == "OK");

                if (aux > 0)
                    cout << "\nMensaje: " << buf << endl;
                else
                    cout << "ERROR RECIBIENDO DATOS\n";

            }

        }

    // Se sale si no enviamos ningún caracter
    } while (ndata > 0);

    // Cerramos el puerto USB
    CerrarUSB(fd);

    cout << "\nFin del programa.\n\n";

    return 0;

}
