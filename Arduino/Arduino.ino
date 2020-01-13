/*
  Program written by JelleWho
  Board: https://dl.espressif.com/dl/package_esp32_index.json

  Dependencies (NOT INCLUDED!!, INCLUDE YOUR OWN OR INCLUDE IT YOURSELF)
  https://github.com/jellewie/Arduino-WiFiManager
  https://github.com/jellewie/Arduino_DIYHUE_switch
*/
#define IFTTT

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <WebServer.h>

WebServer server(80);
WiFiClientSecure client;

void setup() {
  WiFiManager_Start();      //Setup all WIFI stuff (NOT INCLUDED!!, INCLUDE YOUR OWN OR INCLUDE IT YOURSELF)
  
  server.on("/set",       IFTTT_handle_Set);
  server.on("/register",  IFTTT_handle_Register);
  server.begin();
  
  //Serial.begin(115200);
  //Serial.println(WiFi.localIP()); //Just send it's IP on boot to let you know
}

void loop() {
  server.handleClient();      //handle the (IFTTT) web trafic
}
