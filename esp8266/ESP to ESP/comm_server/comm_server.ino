
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>


char buffer[20];
char charbuf[50];
char charbuf2[50];
extern "C" {
#include "user_interface.h"
}

// Internet router credentials
const char* ssid = "Esp Server";
const char* password = "123123123";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(74880);
  WiFi.mode(WIFI_AP_STA);

  Wire.pins(0, 2); //on ESP-01.
  Wire.begin();
  StartUp_OLED(); // Init Oled and fire up!
  Serial.println("OLED Init...");
  clear_display();
  sendStrXY(" Temperature ", 0, 1); // 16 Character max per line with font set
  sendStrXY(" Monitoring project   ", 2, 1);
  sendStrXY("   By Imesh Sachinda     ", 2, 1);
  delay(4000);
  Serial.println("Setup done");
  
  setupAccessPoint();
}
// Handling the / root web page from my server
void handle_index() {
  server.send(200, "text/plain", "Get out from my server!");
}

// Handling the /feed page from my server
void handle_feed() {
  String t = server.arg("temp");
  String h = server.arg("temp_2");

  server.send(200, "text/plain", "This is response to client");
  
  //setupStMode(t, h);
  Serial.println(t);
  Serial.println(h);
  
  t.toCharArray(charbuf,50);
  h.toCharArray(charbuf2,50);
  clear_display();
  
  sendStrXY(charbuf, 0, 1); // 16 Character max per line with font set
  sendStrXY(charbuf2, 1, 1);
  delay(2000);
  
}

void setupAccessPoint(){
  Serial.println("** SETUP ACCESS POINT **");
  Serial.println("- disconnect from any other modes");
  WiFi.disconnect();
  Serial.println("- start ap with SID: "+ String(ssid));
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("- AP IP address is :");
  Serial.print(myIP);
  setupServer();
}

void setupServer(){
  Serial.println("** SETUP SERVER **");
  Serial.println("- starting server :");
  server.on("/", handle_index);
  server.on("/feed", handle_feed);
  server.begin();
}

void loop() {
  server.handleClient();
}
