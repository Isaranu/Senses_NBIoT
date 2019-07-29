/*
Recommended use Arduino MEGA 2560 with AIS NB-IoT shield
*/

#include "Senses_NBIoT.h"
#include "DHT.h"

Senses_NBIoT mynbiot;

const long interval = 10;  /* set delay loop second */
unsigned long previousMillis = 0;

String userid = "your-senses-user-id";
String key = "your-registered-device-key";

#define DHTPIN 7 /* Connected DHT22 to D7 on Arduino MEGA */
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float t,h;

void setup(){
  Serial.begin(9600);
  mynbiot.init();
  
  previousMillis = millis();
}
void loop(){
  
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval*1000){

     /* - DHT sensor reading - */
     t = dht.readTemperature();
     h = dht.readHumidity();

     if (isnan(t) || isnan(h)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
     }

     Serial.println("Temperature is " + String(t) + " celcuis");
     Serial.println("Humidity is " + String(h) + " %RH");
     Serial.println("----------------------------------------");
     
     mynbiot.send(userid, key, 1, t); /* mynbiot.send(userid, key, slotnumber, data); */  
     mynbiot.send(userid, key, 2, h); /* mynbiot.send(userid, key, slotnumber, data); */  
     
     previousMillis = currentMillis;
    }

}
