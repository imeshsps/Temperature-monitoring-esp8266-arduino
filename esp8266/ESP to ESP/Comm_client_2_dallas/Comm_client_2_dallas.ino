/*
Geekstips.com
IoT project - Communication between two ESP8266 - Talk with Each Other
ESP8266 Arduino code example
*/

#include <OneWire.h>
#include <DallasTemperature.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define ONE_WIRE_BUS D1


OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

char temperatureString[6];
float temperature;
float temp;

// AP Wi-Fi credentials
const char* ssid = "Esp Server";
const char* password = "123123123";

// Local ESP web-server address
String serverHost = "http://192.168.4.1/feed";
String data;
// DEEP_SLEEP Timeout interval
int sleepInterval = 5;
// DEEP_SLEEP Timeout interval when connecting to AP fails
int failConnectRetryInterval = 2;
int counter = 0;

float h;
float t;
// Static network configuration
IPAddress ip(192, 168, 4, 4);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

//DHT dht(DHTPIN, DHT22);
WiFiClient client;

void setup() {
  ESP.eraseConfig();
  WiFi.persistent(false);
  Serial.begin(74880);
  Serial.println();
  Serial.println("**************************");
  Serial.println("**************************");
  Serial.println("******** BEGIN ***********");
  Serial.println("- start Dallas Temperature sensor");
  //dht.begin();
  delay(500);
  Serial.println("- set ESP STA mode");
  WiFi.mode(WIFI_STA);
  Serial.println("- connecting to wifi");
  WiFi.config(ip, gateway, subnet); 
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    if(counter > 20){
       Serial.println("- can't connect, going to sleep");    
      // hibernate(failConnectRetryInterval);
    }
    delay(500);
    Serial.print(".");
    counter++;

    DS18B20.begin();
  }
  
 /* Serial.println("- wifi connected");
  Serial.println("- read DHT sensor");
  //readDHTSensor();
  Serial.println("- build DATA stream string");
  buildDataStream();
  Serial.println("- send GET request");
  sendHttpRequest();
  Serial.println();
  Serial.println("- got back to sleep");
  Serial.println("**************************");
  Serial.println("**************************");
  //hibernate(sleepInterval);
*/
}

void sendHttpRequest() {
  HTTPClient http;
  http.begin(serverHost);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.POST(data);
  http.writeToStream(&Serial);
  http.end();
}

void buildDataStream() {
  
  data = "temp_2=";
  data += temp;
  /*data += String(t);
  data += "&hum=";
  data += String(h);*/
  Serial.println("- data stream: "+data);
}


/*void hibernate(int pInterval) {
  WiFi.disconnect();
  ESP.deepSleep(10 * 600000 * pInterval, WAKE_RFCAL);
  delay(100);
}*/

float getTemperature() {
  
  do {
    DS18B20.requestTemperatures(); 
    temp = DS18B20.getTempCByIndex(0);
    delay(100);
  } while (temp == 85.0 || temp == (-127.0));
  return temp;
}

void loop() {

   float temperature = getTemperature();

  dtostrf(temp, 2, 2, temperatureString);
  // send temperature to the serial console
  Serial.println(temperatureString);
  
  while (WiFi.status() != WL_CONNECTED) {
    

    WiFi.begin(ssid, password);
       Serial.println("Trying to connect");    
       delay(100);
      // hibernate(failConnectRetryInterval);
    }
  Serial.println("- wifi connected");
  
  
  Serial.println("- build DATA stream string");
  buildDataStream();
  Serial.println("- send GET request");
  sendHttpRequest();
  Serial.println();
  Serial.println("Done");
  Serial.println("**************************");
  Serial.println("**************************");
  
  
  delay(1000);
  
  }
