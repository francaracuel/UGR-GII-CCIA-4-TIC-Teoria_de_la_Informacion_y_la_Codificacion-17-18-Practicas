////////////////////////////////////////////////////////////////////////////////
// Francisco Javier Caracuel Beltrán
//
// Teoría de la Información y la Codificación - TIC - GII - CCIA
//
// Curso 2017-2018
//

// Ciclo de reloj del procesador: 16MHz
#define F_CPU 16000000UL

// Velocidad (en baudios) de las comunicaciones serie
#define UART_BAUD_RATE 9600

#include <avr/io.h>
#include <avr/interrupt.h>
#include <uart.h>
#include <util/delay.h>

#define BLINK_DELAY_MS 1000

int main(void) {

  // Byte de datos recibido por puerto serie
  // El byte menos significativo es el dato
  // El segundo byte menos significativo contiene 
  //   información de error
  unsigned int c;


  // Inicialización del puerto UART con la velocidad 
  //  en baudios del puerto, y la velocidad del procesador      
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
  
  // Activación de las interrupciones hardware para
  //  control del puerto serie  
  sei();
  
  
  
  
  // Pin 0 del puerto B del micro puesto como salida
    DDRB |= _BV(DDB4);
    

  while (1) {
      
      // Se manda la señal de voltaje alto al pin 0 del puerto B
        PORTB |= _BV(PORTB4);
        _delay_ms(BLINK_DELAY_MS);
        
        // Se manda la señal de voltaje bajo al pin 0 del puerto B
        PORTB &= ~_BV(PORTB4);
        _delay_ms(BLINK_DELAY_MS);
        
        
        
        
        
        
        
        

      // Se recoge el byte desde el puerto UART
      c = uart_getc();
      
      // Flag sin datos activado. Se duerme
      if(c & UART_NO_DATA){
          _delay_ms(1);
      
      // Error de recepción de la trama de datos. Se envía el mensaje
      } else if(c & UART_FRAME_ERROR){
          
          uart_puts_P("Error recibiendo la trama.\n");
          
      // Error de recepción de dato más rápido de lo que se pudo leer el 
      //anterior
      } else if(c & UART_OVERRUN_ERROR){
          
          uart_puts_P("Error: La interrupción no pudo leer dato antes de recibir el siguiente.\n");
          
      // Error de recepción: Buffer lleno. No estamos leyendo tan rápido como
      // nos envían
      } else if(c & UART_BUFFER_OVERFLOW){
          
          uart_puts_P("Error: El buffer está lleno. No se puede leer tan rápido como se envía.\n");
          
      // Todo ok. Se responde con el mismo carácter
      } else{
          
          uart_putc((unsigned char)c);
          
      }

  }

  return 0;
  
}
