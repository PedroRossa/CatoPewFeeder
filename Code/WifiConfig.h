/*
    WifiConfig.h - Library for manage ESP8266 wifi connection.
    Created by Pedro Rossa, January 4, 2022.
    Released into the public domain.
*/
#ifndef WifiConfig_h
#define WifiConfig_h

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "WifiCredentials.h"

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.1.1";
const uint16_t port = 3000;

ESP8266WiFiMulti WiFiMulti;

static unsigned long last_timer_in_millis = millis();

void initWifi()
{
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP(ssid, password);

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while (WiFiMulti.run() != WL_CONNECTED) 
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  
    delay(500);
}

void freeHeap(uint seconds_to_repeat)
{
    if (millis() - last_timer_in_millis > (seconds_to_repeat * 1000)) 
    {
        last_timer_in_millis = millis();
        Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
    }
}

#endif