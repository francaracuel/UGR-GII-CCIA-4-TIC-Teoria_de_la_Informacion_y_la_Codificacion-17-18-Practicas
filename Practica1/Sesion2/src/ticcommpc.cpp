#include <ticcommpc.h>
//#include <rs232.h>
//#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


// Inicializar el puerto USB en el dispositivo dado por argumento

int InicializarUSB(const char *portname) {

    // Descriptor de fichero para abrir el puerto
    int fd;
    
    // Estructura para control del puerto USB
    struct termios toptions;
    
    // Se abre el puerto para E/S, sin bloqueo del puerto
    fd = open(portname, O_RDWR | O_NOCTTY);
    
    if(fd == -1){
        
        return -1;
        
    }
    
    // Se coge la configuración actual de dispositivos /dev/tty
    tcgetattr(fd, &toptions);
    
    cfsetispeed(&toptions, B9600);
    cfsetospeed(&toptions, B9600);
    
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
    
    
    toptions.c_cflag &= ~CRTSCTS;
    
    toptions.c_cflag |= CREAD | CLOCAL;
    
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
    
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    
    toptions.c_oflag &= ~OPOST;
    
    toptions.c_cc[VMIN] = 1;
    
    toptions.c_cc[VTIME] = 0;
    
    tcsetattr(fd, TCSANOW, &toptions);
    
    
    usleep(2000000);
    
    tcflush(fd, TCIFLUSH);
    
    return fd;
    
    
}

void CerrarUSB(int &pd){

    close(pd);
    pd = -1;
    
}

int Dormir(int ms){

#ifdef _WIN32
    Sleep(ms); // Dormir 100 ms para windows
#else
    usleep(1000 * ms); // Dormir 100 ms para linux (microsegundos)
#endif

}

bool sendUSB(int &pd, char *data){

    // A IMPLEMENTAR. EJERCICIO DEL CUADERNO DE PRACTICAS
    
}

bool receiveUSB(int &fd, char *data){

    // A IMPLEMENTAR. EJERCICIO DEL CUADERNO DE PRACTICAS
    
}





