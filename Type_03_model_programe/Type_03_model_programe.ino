#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// This programe does not include programe for display data on a display
// this is just to get a serial output to computer by Hardware serial on AT328p
//RF24 radio(7, 8);
RF24 radio(9, 10);


const byte rxAddr[6] = "00001";

void setup()
{
  while (!Serial);
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, rxAddr);
  
  radio.startListening();
}

void loop()
{
  if (radio.available())
  {
    int text[3];
    radio.read(&text, sizeof(text));
    for (int j=0;j<3;j++){
      if(j==0){
        
        Serial.print("Station 1 Temperature : " );
        Serial.println(text[j]);
        }
        else if(j==1){
        Serial.print("Station 2 Sensor 1 Temperature : " );
        Serial.println(text[j]);
        }
        else if(j==2){
        Serial.print("Station 2 Sensor 2 Temperature : " );
        Serial.println(text[j]);
        Serial.println();
        }
      
      
      }
    
  }
  
}
