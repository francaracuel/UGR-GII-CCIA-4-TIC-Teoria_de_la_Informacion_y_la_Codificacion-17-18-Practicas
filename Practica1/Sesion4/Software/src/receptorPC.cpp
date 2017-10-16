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

using namespace std;

// Puerto de comunicaciones con arduino
#define USBPORT "/dev/ttyACM0"

// Programa principal
int main(int argc, char *argv[]){
    
    // Descriptor de fichero del puerto USB
    int fd;
    
    // Buffer de salida. Tamaño máximo de 128 caracteres.
    char buf[129];
    
    // Se inicializa el puerto
    fd = InicializarUSB(USBPORT);
    
    if(fd==-1){
        cout << "Error inicializando el puerto " << USBPORT << endl;
        return 0;
    }
    
    cout << "Comenzando a leer...\n" << endl;
    
    // Bucle principal
    while(1){
        
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