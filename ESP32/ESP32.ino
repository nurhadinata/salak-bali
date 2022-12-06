#include <ThingerESP32.h>
#include "arduino_secrets.h"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

#define THINGER_SERIAL_DEBUG

#define RELAY_PIN     19
#define test          21
#define MOISTURE_PIN  32

void setup() {
  // open serial for debugging
  Serial.begin(115200);
  pinMode(MOISTURE_PIN, INPUT);
  pinMode(AUTO_PIN, OUTPUT); 
  pinMode(RELAY_PIN, OUTPUT); 
  //pinMode(16, OUTPUT);
  
  thing.add_wifi(SSID, SSID_PASSWORD);

  
  int moisturePercent =0;
   
    // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  //thing["relay"] << digitalPin(16);
    
  thing["relay"] << [](pson& in){
    if(in.is_empty()){
      in = (bool) digitalRead(AUTO_PIN);
    }else{
      digitalWrite(AUTO_PIN, in ? HIGH : LOW);     
    };    
  };
  
  

  //resource output example (i.e. reading a sensor value)
  //thing["millis"] >> outputValue(millis());
  thing["moisture"] >> [](pson& out){
    out = analogRead(MOISTURE_PIN);
    if((int) out<2000 && (bool) digitalRead(AUTO_PIN)){
       digitalWrite(RELAY_PIN, HIGH);     
    }else{
      digitalWrite(RELAY_PIN, LOW);      
    };
  };
  thing["auto status"] >> [](pson& out){
    out = (bool) digitalRead(AUTO_PIN);
  };

  thing["relay status"] >> [](pson& out){
    out = (bool) digitalRead(RELAY_PIN);
  };

  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  
  thing.handle();  
  //int value = analogRead(34);
    
  //Serial.print("Value : ");
  //Serial.println(value);

  //delay(1000);  
}