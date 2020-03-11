#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

#define ssid "baltic mobile"
#define pass "05dana09"

#define device1 "bedroom light"

fauxmoESP fauxmo; 
void wifi() 
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
    
    delay(100);
  }
}


void setup() 
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
 
  wifi();
  fauxmo.createServer(true);
  fauxmo.setPort(80); 
  fauxmo.enable(true);
  fauxmo.addDevice(device1);
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
  Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d/n",device_id, device_name, state ? "ON" : "OFF");
    if (strcmp(device_name,"bedroom light") == 0)
    {
      if (state)
      {
        digitalWrite(2, HIGH);
      }
    else 
      {
        digitalWrite(2, LOW);
        
      }

    }
    });
   
}

    void loop() {
  
  fauxmo.handle();

  
}
