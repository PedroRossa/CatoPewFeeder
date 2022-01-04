/*
    FauxmoManager.h - Script to configure and use FauxmoESP to connect the feeder to alexa
    Created by Pedro Rossa, January 4, 2022.
    Released into the public domain.
*/
#ifndef FauxmoManager_h
#define FauxmoManager_h

#include "fauxmoESP.h"

fauxmoESP fauxmo;

bool active_right_feeder_command = false;
//bool active_left_feeder_command = false;

//The value set to these defines will be the words used on alexa to activate and deactivate the feeders
#define ID_RIGHT_FEDDER "alimentador direito"
//#define ID_LEFT_FEDDER "alimentador esquerdo"

void fauxmoOnState()
{
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
  
  // Callback when a command from Alexa is received. 
  // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
  // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
  // Just remember not to delay too much here, this is a callback, exit as soon as possible.
  // If you have to do something more involved here set a flag and process it in your main loop.
        
  Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

  // Checking for device_id is simpler if you are certain about the order they are loaded and it does not change.
  // Otherwise comparing the device_name is safer.

  if (strcmp(device_name, ID_RIGHT_FEDDER) == 0 && state == true)
  { 
    active_right_feeder_command = true;
    fauxmo.setState(ID_RIGHT_FEDDER, false, 0);
  }
  
  //if (strcmp(device_name, ID_LEFT_FEDDER) == 0 && state == true)
  //{ 
  //  active_left_feeder_command = true;
  //  fauxmo.setState(ID_LEFT_FEDDER, false, 0);
  //}
  
  });
}

void initFauxmo()
{
    // By default, fauxmoESP creates it's own webserver on the defined port
    // The TCP port must be 80 for gen3 devices (default is 1901)
    // This has to be done before the call to enable()
    fauxmo.createServer(true); // not needed, this is the default value
    fauxmo.setPort(80); // This is required for gen3 devices

    // You have to call enable(true) once you have a WiFi connection
    // You can enable or disable the library at any moment
    // Disabling it will prevent the devices from being discovered and switched
    fauxmo.enable(true);

    // Add virtual devices
    fauxmo.addDevice(ID_RIGHT_FEDDER);
    //fauxmo.addDevice(ID_LEFT_FEDDER);

    fauxmoOnState();
}

#endif