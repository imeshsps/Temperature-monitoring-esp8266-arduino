/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates: wifi_client_01.ino
 */
#include <ESP8266WiFi.h>
#include <Wire.h>


//byte ledPin = 2;
char ssid[] = "i2s";               // SSID of your home WiFi
char pass[] = "123123123";               // password of your home WiFi
WiFiServer server(80);                    

IPAddress ip(192, 168, 43, 135);            // IP address of the server
IPAddress gateway(192,168,43,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network

void setup() {
  Serial.begin(115200);                   // only for debug
  Wire.pins(0, 2); //on ESP-01.
  Wire.begin();
  StartUp_OLED(); // Init Oled and fire up!

  Serial.println("OLED Init...");
  clear_display();
  sendStrXY(" Temperature ", 0, 1); // 16 Character max per line with font set
  sendStrXY(" Monitoring project   ", 2, 1);
  sendStrXY("   By Imesh Sachinda     ", 2, 1);
  delay(2000);

  //WiFi.config(ip, gateway, subnet);       // forces to use the fix IP
  WiFi.begin(ssid, pass);                 // connects to the WiFi router
  clear_display();
  sendStrXY(" Connecting to wifi..", 2, 1);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    
    delay(500);
  }
  server.begin();                         // starts the server
  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());  // some parameters from the network
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());
  Serial.print("Networks: "); Serial.println(WiFi.scanNetworks());
  clear_display();
  sendStrXY(" Connected..", 0, 1);
  delay(2000);
  
  
  //pinMode(ledPin, OUTPUT);
}

void loop () {
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      //digitalWrite(ledPin, LOW);  // to show the communication only (inverted logic)
      Serial.println(".");
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client.Temperatue : "); Serial.println(request);
      clear_display();
      sendStrXY(" Temperatue ", 0, 1);
      char charbuf[50];
       request.toCharArray(charbuf,50);
      sendStrXY(charbuf, 2, 1);
      client.flush();
      client.println("Hi client! No, I am listening.\r"); // sends the answer to the client
      //digitalWrite(ledPin, HIGH);
    }
    client.stop();                // tarminates the connection with the client
  }
}
