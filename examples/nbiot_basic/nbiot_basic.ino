#include "Senses_NBIoT.h"

Senses_NBIoT mynbiot;

const long interval = 10;  /* set delay loop second */
unsigned long previousMillis = 0;

String userid = "your-senses-user-id";
String key = "your-registered-device-key";

float t,h;

void setup(){
  Serial.begin(9600);
  mynbiot.init();
  
  previousMillis = millis();
}
void loop(){
  
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval*1000){

     float random_number = random(10,50);
     mynbiot.send(userid, key, 1, random_number); /* mynbiot.send(userid, key, slotnumber, data); */  
      
     previousMillis = currentMillis;
    }

}
