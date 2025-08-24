/**
 * @brief Communication library
 */

#ifndef _HARDWARE_H
#define _HARDWARE_H

#ifndef _WIN64
#include <WiFi.h>
#include <HTTPClient.h>
#include "src/CommonData.h"

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

  // Setup I/O
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(INPUT_PIN, INPUT_PULLUP);

  // Wait for activate signal
  while (digitalRead(INPUT_PIN)) {
    delay(10);
  }

  //Setup WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.config(
    IPAddress(IP_ADD_1, IP_ADD_2, IP_ADD_3, IP_ADD_4),
    IPAddress(IP_ADD_1, IP_ADD_2, IP_ADD_3, IP_ADD_4),
    IPAddress(NETMASK_1, NETMASK_2, NETMASK_3, NETMASK_4));

  // Wait for WiFi connect
  WiFiReconnect();

  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void SendMessage(data_pack_t byteData) {
  HTTPClient http;

  // Init server path
  char serverPath[30] = { 0 };
  sprintf(serverPath, "http://%d.%d.%d.%d:%d", IP_ADD_1, IP_ADD_2, IP_ADD_3, (uint8_t)MODULE_NAME::Transporter, (uint8_t)MODULE_NAME::Transporter);

  String payload = "";
  JsonDocument jsonDoc;

  // Begin request
  http.begin(serverPath);
  http.addHeader("Content-Type", "application/json");

  // Convert struct to json
  jsonDoc[STR(source)] = byteData.source;
  jsonDoc[STR(base_msg)] = byteData.base_msg;
  jsonDoc[STR(msg)] = byteData.msg;
  jsonDoc[STR(data)] = byteData.data;

  // Convert json to string
  String jsonDocStr = "";
  serializeJson(jsonDoc, jsonDocStr);

  // Post data
  int32_t httpResponseCode = http.POST(jsonDocStr);

  if (httpResponseCode == HTTP_OK) {
    // Get response string
    payload = http.getString();
    Serial.println(payload);

    // Convert message data to json
    jsonDoc.clear();
    deserializeJson(jsonDoc, payload);

    // Set json data common data
    sys_host::JsonResponse.SetValue(jsonDoc);
  } else {
    // Re-send request
    SendMessage(byteData);
  }

  // End request
  http.end();
}

#endif
#endif  // _HARDWARE_H
