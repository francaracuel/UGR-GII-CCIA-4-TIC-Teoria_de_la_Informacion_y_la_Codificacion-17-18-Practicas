#include <cstring>
#include <ticcommpc.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>

using namespace std;

// Puerto de comunicaciones con arduino

/* MODIFICAR EL PUERTO CON AQUEL DONDE SE VAYA A CONECTAR ARDUINO */
#define DEVICE "/dev/ttyACM0"



int main(int argc, char *argv[]) {

  int fd; // Descriptor de puerto del puerto USB
  char buf[129]; // Buffer de salida. Tamaño máximo de 128 caracteres
  int ndata; // Número de datos en el buffer
  int aux;

  // Inicializamos puerto

	fd = InicializarUSB(USBPORT);

  if (fd == -1){
    cout << "Error inicializando puerto " << USBPORT << endl;
    return 0;
  }

  // Bucle hasta que salgamos (cuando no introduzcamos nada)
  do {

	 cout << "Escriba algo para enviar a Arduino: ";
   cin.getline(buf,128);

   ndata= strlen(buf); //Tamaño del buffer de salida

   if (buf = "ON" || buf = "OFF"){
    aux = write(fd,buf,ndata);
    tcflush(fd,TCIFLUSH);
    cout << "Bytes enviados " << aux << "/" << ndata << endl;

    // Comprobamos errores en el envío
    if (aux < ndata){
      cout << "Error, en el buffer tiene " << ndata << " bytes pero se enviaron " << aux << endl;
      ndata = 0;
    }

    // Si se envió algun dato, esperamos respuesta de Arduino
    if (aux>0){
      aux = read(fd,buf,128);
      if(aux>0)
        cout << "\tMensaje: " << buf << endl << endl;
      else
        cout << "\tERROR RECIBIENDO DATOS\n";
    }
   }
  // Se sale si no enviamos ningún caracter
  } while (ndata > 0);


  // Cerramos el puerto USB

	CerrarUSB(fd);


  cout <<"\nFin del programa.\n\n";
  return 0;
}
