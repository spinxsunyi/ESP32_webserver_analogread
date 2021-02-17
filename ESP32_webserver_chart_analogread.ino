/*********
 * Eka Yudhi Pratama
 * 18/02/2021
 * Reading analog voltage and display on webserver ESP32.
 * This project build based on good work of:
 
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#ifdef ESP32
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#else
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#endif

// Replace with your network credentials
const char* ssid = "SSID";
const char* password = "passwd";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readA34() {
  float p = analogRead(34);
  Serial.println(p);
  return String(p);
}
String readA35() {
  float p = analogRead(35);
  Serial.println(p);
  return String(p);
}
String readA36() {
  float p = analogRead(36);
  Serial.println(p);
  return String(p);
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  bool status;

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });
  server.on("/A34", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", readA34().c_str());
  });
  server.on("/A35", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", readA35().c_str());
  });
  server.on("/A36", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", readA36().c_str());
  });

  // Start server
  server.begin();
}

void loop() {

}
