#include <ICSC.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);

float temp;
char itemp;

DallasTemperature sensors(&oneWire);

//SoftwareSerial mySerial(10, 11); // RX, TX
SoftwareSerial mySerial(5, 6);


void setup()
{
  ICSC.begin(3, 115200,2);
 
   
   mySerial.begin(9600);
   mySerial.println("Device Started..");
   
   sensors.begin();
   
  
}

void loop()
{
      sensors.requestTemperatures();
      temp = sensors.getTempCByIndex(0);

      if(temp == -127){

         ICSC.send(1, 'P', 10, "z");
      mySerial.println("Senror fault");
        
        }
      
      else{
      itemp = (char) temp;
      
      ICSC.send(1, 'P', 10, (char *)&itemp);
      mySerial.print("Temperature Sent to Serial Bus");
      mySerial.println("Temperature : ");
      mySerial.print(temp);
      mySerial.println(" C");
}
      delay(500);
    
}
