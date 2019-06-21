/* This code includes progame to connect a I2C display into this model.
 *  at testing i had a display connected to this model.*/

#include <ICSC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <SPI.h>
//#include <nRF24L01.h>
//#include <RF24.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
SoftwareSerial mySerial(5, 6);


RF24 radio(9, 10);

const byte rxAddr[6] = "00001";

int i=0;
int k=0;
int j=0;
int l=0;
int m=0;

int16_t temp1;

int16_t temp2_1;
int16_t temp2_2;
int16_t temp2_3;

int16_t text[3];





void setup()
{
  mySerial.begin(9600);
  ICSC.begin(1, 115200,2);
  ICSC.registerCommand('P', &p_received);
  ICSC.registerCommand('Q', &q_received);
  ICSC.registerCommand('R', &r_received);
  //ICSC.registerCommand('S', &s_received);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Display initialized..!");
  display.display();
  delay(500);
  display.clearDisplay();
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();
}

void loop()
{
  
  ICSC.process();
  i++;
  k++;
  l++;
  m++;
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  p_print();
  q_print();
  
  r_print();
  mySerial.println("Running..");

  
  text[0]=temp1;
  text[1]=temp2_1;
  text[2]=temp2_2;
  
  radio.write(&text, sizeof(text));
  
 // s_print();
  delay(200);
  
 
  
  
   display.setCursor(0,26);
  if(j==0){
  j=j+1;
  }
  else if(j==1){
    display.println(".");
    j=j+1;
  }
  else if(j==2){
    display.println("..");
    j=j+1;
  }
  else if(j==3){
    display.println("...");
    j=0;
  }
  else{j=0;}
  
    
  display.display();
  delay(250);
  
}

void p_received(unsigned char src, char command, unsigned char len, char *datap)
{   

  i = 0;
  int16_t *value = (int16_t *)datap;
  
   temp1 = *value;
   mySerial.println("P received data : ");
  mySerial.println(temp1);
}

void p_print(){
  
  if(i>=10){
     display.print("Station 1 fail");
     }

   else if(temp1==122){
    display.print("Station 1 sensor Fail ");
   
  }
  else{
  display.print("Station 1 : ");
  display.print(temp1);
 mySerial.println("P temp : ");
  mySerial.println(temp1);
  display.println(" C");
  }
  }



void q_print(){

  display.setCursor(0,8);
  
  if(k>=10){
     display.print("Station 2 fail");
     }

   else if(temp2_1 == 122){
    display.print("S2 Sen 1 sensor Fail ");
   
  }
  else{
  display.print("S02 sen 1 : ");
  display.print(temp2_1);
  mySerial.println("Q temp : ");
  mySerial.println(temp2_1);
  display.println(" C");
  }
  }



void r_print(){

  display.setCursor(0,16);
  
  if(l>=10){
     display.print("Station 2 fail");
     }

   else if(temp2_2==122){
    display.print("S2 Sen 2 sensor Fail ");
   
  }
  else{
  display.print("S02 sen 2 : ");
  display.print(temp2_2);
  display.println(" C");
  }
}

  

/*void s_print(){
  
  display.setCursor(0,24);
  
  if(m>=10){
     display.print("Station 2 fail");
     }

   else if(temp2_3==122){
    display.print("S2 Sen 3 sensor Fail ");
   
  }
  else{
  display.print("S02 sen 3 : ");
  display.print(temp2_3);
  display.println(" C");
  }
  }
  */
void q_received(unsigned char src, char command, unsigned char len, char *dataq)
{   
  k = 0;
  
  int16_t *value = (int16_t *)dataq;
  
   temp2_1 = *value;
   mySerial.println("Q received data : ");
  mySerial.println(temp2_1);
   
 }

 void r_received(unsigned char src, char command, unsigned char len, char *datar)
{   
  l = 0;
  
  int16_t *value = (int16_t *)datar;
   temp2_2 = *value;
   mySerial.println("R received data : ");
  mySerial.println(temp2_2);
   
 
}

/*void s_received(unsigned char src, char command, unsigned char len, char *datas)
{   
  m = 0;
  
  int16_t *value = (int16_t *)datas;
   temp2_3 = *value;
   Serial1.println("S received data : ");
  Serial1.println(temp2_3);
   
 
}*/




