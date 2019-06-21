#include <ICSC.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

#define ONE_WIRE_BUS 4

#define TEMPERATURE_PRECISION 12

OneWire oneWire(ONE_WIRE_BUS);

float temp;
char itemp;

DallasTemperature sensors(&oneWire);

SoftwareSerial mySerial(10, 11); // RX, TX

/* There are the adresses for the connected sensors.if sensor is
 *  replaced,the adress should change*/
 
uint8_t sen1[8] = {0x28, 0xEE, 0x6B, 0x56, 0x25, 0x16, 0x02, 0xCF};
uint8_t sen2[8] = {0x28, 0xEE, 0x02, 0x72, 0x25, 0x16, 0x02, 0x53};
//uint8_t sen3[8] = {0x28, 0xEE, 0x51, 0x66, 0x25, 0x16, 0x02, 0xBE};

int i = 0;
void setup()
{
  ICSC.begin(2, 115200,2);
 
   
   mySerial.begin(9600);
   mySerial.println("Device Started..");
   
   sensors.begin();

   
  // locate devices on the bus
  mySerial.print("Locating devices...");
  mySerial.print("Found ");
  mySerial.print(sensors.getDeviceCount(), DEC);
  mySerial.println(" devices.");

  // report parasite power requirements
  mySerial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else mySerial.println("OFF");

 /*  // assigns the first address found to insideThermometer
  if (!oneWire.search(sen1)) Serial.println("Unable to find Sensor 1");
  
  if (!oneWire.search(sen2)) Serial.println("Unable to find Sensor 2");

  if (!oneWire.search(sen3)) Serial.println("Unable to find Sensor 3");
*/
   // set the resolution to 9 bit per device
    sensors.setResolution(sen1, TEMPERATURE_PRECISION);
    sensors.setResolution(sen2, TEMPERATURE_PRECISION);
    //sensors.setResolution(sen3, TEMPERATURE_PRECISION);

    mySerial.print("Sensor 01 Resolution: ");
    mySerial.print(sensors.getResolution(sen1), DEC); 
    mySerial.println();

    mySerial.print("Sensor 02 Resolution: ");
    mySerial.print(sensors.getResolution(sen2), DEC); 
    mySerial.println();

   /* mySerial.print("Sensor 03 Resolution: ");
    mySerial.print(sensors.getResolution(sen3), DEC); 
    mySerial.println();*/

   
  
}

void loop()
{
      Serial.print("Requesting temperatures...");
      sensors.requestTemperatures();
      Serial.println("DONE");



      /*if(i==0){
      Sensor_1_temp();
      i=1;
      }
      else if(i==1){
      Sensor_2_temp();
      i=2;
      }
      else{
      Sensor_3_temp();
      i=0;
      }*/
      Sensor_1_temp();
      Sensor_2_temp();

      

      

      delay(500);
    
}

void Sensor_1_temp()
{ 
  
  float tempC1 = sensors.getTempC(sen1);
  
  if(tempC1 == -127){

         ICSC.send(1, 'Q', 10, "z");
      mySerial.println("Senror fault");
        
        }
      else{
        
      char itemp1 = (char) tempC1;
      
      ICSC.send(1, 'Q', 10, (char *)&itemp1);
      mySerial.print("Temperature Sent to Serial Bus");
      mySerial.println("Temperature of Sensor 01 : ");
      mySerial.print(tempC1);
      mySerial.println(" C");
  
}
}

void Sensor_2_temp()
{ 
  
  float tempC2 = sensors.getTempC(sen2);
  
  if(tempC2 == -127){

         ICSC.send(1, 'R', 10, "z");
      mySerial.println("Senror fault");
        
        }
      else{
        
      char itemp2 = (char) tempC2;
      
      ICSC.send(1, 'R', 10, (char *)&itemp2);
      mySerial.print("Temperature Sent to Serial Bus");
      mySerial.println("Temperature of sensor 02 : ");
      mySerial.print(tempC2);
      mySerial.println(" C");
  
}
}

/*void Sensor_3_temp()
{ 
  
  float tempC3 = sensors.getTempC(sen3);
  
  if(tempC3 == -127){

         ICSC.send(1, 'S', 10, "z");
      mySerial.println("Senror fault");
        
        }
      else{
        
      char itemp3 = (char) tempC3;
      
      ICSC.send(1, 'S', 10, (char *)&itemp3);
      mySerial.print("Temperature Sent to Serial Bus");
      mySerial.println("Temperature of sensor 03 : ");
      mySerial.print(tempC3);
      mySerial.println(" C");
  
}
}*/


