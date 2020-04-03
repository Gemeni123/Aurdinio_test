#include "ESP8266WiFi.h"
#include "Homey.h"

const char* ssid = "wififransen"; //your WiFi Name
const char* password = "************";  //Your Wifi Password
int ledPin = 03; 
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  delay(10); 
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.print("Device IP: ");
  Serial.println(WiFi.localIP());

  Homey.begin("ArduinoRandomTest");
  Homey.setClass("sensor");
  Homey.addCapability("measure_temperature");
}

void loop() {
  Homey.loop();

  unsigned long currentMillis = millis();

  if (currentMillis-previousMillis >= 10000) { //Code in this if statement is run once every second
    previousMillis = currentMillis;
    int value = random(40);
    Homey.setCapabilityValue("measure_temperature", value);
    Serial.println("On request, sent random_value: " + String(value) + " to homey");
  }
  
}
