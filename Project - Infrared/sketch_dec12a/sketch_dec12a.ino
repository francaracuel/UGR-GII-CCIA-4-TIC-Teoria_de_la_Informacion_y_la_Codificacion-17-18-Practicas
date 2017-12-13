#include <IRremote.h>
 
const int RECV_PIN = 9;
 
IRrecv irrecv(RECV_PIN);
decode_results results;
 
void setup(){
  
   Serial.begin(9600);
   irrecv.enableIRIn();
   
}
 
void loop(){
  
   if (irrecv.decode(&results)){
    
      PORTB |= 0b00000001;

      Serial.println(results.decode_type);
      
      Serial.println(results.value, BIN);
      irrecv.resume();

      delay(100);
            
   } else{

      PORTB &= 0b11111110;
    
   }
   
}
