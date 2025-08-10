/**
 * @brief Communication library
 */

#ifndef _HARDWARE_H
#define _HARDWARE_H

#ifndef _WIN64
#include <WiFi.h>
#include <HTTPClient.h>
#include "src/CommonDataType.h"

#define BUZZER_PIN 26

void WiFiReconnect() {
  if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(10);
    }

    Serial.println("WiFi re-connected");
  }
}

void Beep(uint16_t frequency, uint16_t duration) {
  tone(BUZZER_PIN, frequency, duration);
}

void HardwareSetup() {
  // Setup serial
  Serial.begin(115200);

  //Setup WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait for WiFi connect
  WiFiReconnect();

  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Setup I/O
  pinMode(BUZZER_PIN, OUTPUT);
}

void SendMessage(data_pack_t byteData) {
  HTTPClient http;

  // Init server path
  char serverPath[30] = { 0 };
  sprintf(serverPath, "http://%d.%d.%d.%d:%d", SV_IP_ADD_1, SV_IP_ADD_2, SV_IP_ADD_3, SV_IP_ADD_4, SV_PORT);

  // Begin request
  http.begin(serverPath);
  http.addHeader("Content-Type", "application/json");

  // Convert struct to json
  JsonDocument jsonDoc;
  jsonDoc[STR(target)] = byteData.target;
  jsonDoc[STR(base_msg)] = byteData.base_msg;
  jsonDoc[STR(msg)] = byteData.msg;
  jsonDoc[STR(data)] = byteData.data;

  // Convert json to string
  char jsonDocStr[MAX_SIZE] = { 0 };
  serializeJson(jsonDoc, jsonDocStr);

  // Post data
  int32_t httpResponseCode = http.POST(jsonDocStr);

  if (httpResponseCode == HTTP_OK) {
    String payload = http.getString();
    Serial.println(payload);
  } else {
    // Re-send request
    SendMessage(byteData);
  }

  // End request
  http.end();
}

#endif
#endif  // _HARDWARE_H
