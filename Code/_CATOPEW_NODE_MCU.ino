#include "WifiConfig.h"
#include "DistanceChecker.h"
#include "Feeder.h"
#include "FauxmoManager.h"

const uint time_in_mili_open = 2000;
const int feeder_power_led = D2;

DistanceChecker distanceChecker(D0, D1);

Feeder right_feeder(D3, D4, 115, 70);
//Feeder left_feeder(D5, D6, 115, 70);

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("STARTING CATOPEW Feeder...");
  
  pinMode(feeder_power_led, OUTPUT);

  initWifi();
  initFauxmo();
  
  digitalWrite(feeder_power_led, HIGH);
}

void loop() 
{  
  // fauxmoESP uses an async TCP server but a sync UDP server
  // Therefore, we have to manually poll for UDP packets
  fauxmo.handle();
 
  freeHeap(5);

  if(active_right_feeder_command)
  {
    Serial.println("activate right feeder");
    
    right_feeder.openAndCloseAfterMiliseconds(time_in_mili_open);
    distanceChecker.serialPrintDebugDistance();
    
    active_right_feeder_command = false;
  }
}