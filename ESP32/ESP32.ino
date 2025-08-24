#include <algorithm>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include "src/CD74HC4067.h"
#include "src/StringSplitter.h"
#include "src/ArduinoJson-v7.4.1.h"
#include "src/CommonDataType.h"

#define MODULE_SEL_MUX_ADD_0 13
#define MODULE_SEL_MUX_ADD_1 12
#define MODULE_SEL_MUX_ADD_2 14
#define MODULE_SEL_MUX_ADD_3 27
#define MODULE_SEL_MUX_SIG 26
#define MAX_CHANNEL 16

#define BUZZER_PIN 22

#define FIRST_MODULE_OFFSET (uint8_t) MODULE_NAME::Wires

WebServer server(IP_ADD_4);
CD74HC4067 moduleSelectMux(MODULE_SEL_MUX_ADD_0, MODULE_SEL_MUX_ADD_1, MODULE_SEL_MUX_ADD_2, MODULE_SEL_MUX_ADD_3);

struct module_info_t {
  std::vector<uint8_t> listSelectedIndex;
  uint8_t currentIndex = 0;
  bool isStopAll = false;
} SelectModuleInfo;

void SelectModule(uint8_t channel) {
  digitalWrite(MODULE_SEL_MUX_SIG, LOW);
  moduleSelectMux.channel(channel);
  delay(10);
  digitalWrite(MODULE_SEL_MUX_SIG, HIGH);

  Serial.printf("Selected module #%d: %s\n", channel + 1, map_MODULE_NAME[(MODULE_NAME)(channel + FIRST_MODULE_OFFSET)].c_str());
  tone(BUZZER_PIN, BEEP_FRE, BEEP_INCREASE_DURATION);
}

void SendMessageToClient(uint8_t moduleNum, uint32_t msg) {
  HTTPClient http;

  // Init server path
  char serverPath[30] = { 0 };
  sprintf(serverPath, "http://%d.%d.%d.%d:%d", IP_ADD_1, IP_ADD_2, IP_ADD_3, moduleNum, moduleNum);

  // Begin request
  http.begin(serverPath);
  http.addHeader("Content-Type", "application/json");

  // Post message
  http.POST(String(msg));

  // End request
  http.end();
}

String SendMessageToHostTimer(const data_pack_t& byteData) {
  HTTPClient http;

  // Init server path
  char serverPath[30] = { 0 };
  sprintf(serverPath, "http://%d.%d.%d.%d:%d", IP_ADD_1, IP_ADD_2, IP_ADD_3, (uint8_t)MODULE_NAME::HostTimer, (uint8_t)MODULE_NAME::HostTimer);

  String payload = "";

  // Begin request
  http.begin(serverPath);
  http.addHeader("Content-Type", "application/json");

  // Convert struct to json
  JsonDocument jsonDoc;
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
  } else {
    // Re-send request
    payload = SendMessageToHostTimer(byteData);
  }

  // End request
  http.end();

  return payload;
}

String ProcessRequest(JsonDocument& jsonDocIn, data_pack_t& messageStruct) {
  String response = "Process request done!";

  switch (messageStruct.msg) {
    case WM_SET_CLIENTSTATE:
      {
        // Get list of selected module
        JsonArray listSelectedModule = jsonDocIn.as<JsonArray>();

        // Delete first unuse 2 elements (MIN, HostTimer)
        for (uint8_t i = 0; i < FIRST_MODULE_OFFSET; i++) {
          listSelectedModule.remove(0);
        }

        for (uint8_t i = 0; i < listSelectedModule.size(); i++) {
          // If selected module is ON
          if ((MODULE_STATUS)listSelectedModule[i].as<uint8_t>() == MODULE_STATUS::ON) {
            // Activate module
            SelectModule(i);

            // Add current module num to selected module list
            SelectModuleInfo.listSelectedIndex.push_back(i);
          }
        }

        listSelectedModule.clear();
      }
      break;
    case WM_CLIENT_RESPONSE:
      {
        // Process stop all module
        if (SelectModuleInfo.isStopAll) {
          Serial.printf("Module #%d is stopped!\n", SelectModuleInfo.listSelectedIndex[SelectModuleInfo.currentIndex]);

          // Update next index for selected module list
          SelectModuleInfo.currentIndex++;

          // Push signal to HIGH
          digitalWrite(MODULE_SEL_MUX_SIG, HIGH);
          tone(BUZZER_PIN, BEEP_FRE, BEEP_INCREASE_DURATION);

          /* Continue to next module index... */

          // All module are stopped
          if (SelectModuleInfo.currentIndex == SelectModuleInfo.listSelectedIndex.size()) {
            // Reset info
            SelectModuleInfo.currentIndex = 0;
            SelectModuleInfo.isStopAll = false;

            // Send message stop complete to HostTimer
            messageStruct.msg = WM_STOP_COMPLETE;
            SendMessageToHostTimer(messageStruct);

            Serial.println("All module are stopped!");
          }
        }
      }
      break;
    case WM_STOP_ALL:
      {
        // Set stop all flag
        SelectModuleInfo.isStopAll = true;
      }
      break;
    default:
      {
        // Forward message to HostTimer
        response = SendMessageToHostTimer(messageStruct);
      }
      break;
  }

  return response;
}

void OnMainServer() {
  JsonDocument jsonMsg;
  JsonDocument jsonData;
  data_pack_t messageStruct = { 0 };

  // Get POST data
  String postBody = server.arg("plain");

  // Convert message string to json
  deserializeJson(jsonMsg, postBody);

  // Get message into struct
  strcpy(messageStruct.source, jsonMsg[STR(source)].as<const char*>());
  messageStruct.base_msg = jsonMsg[STR(base_msg)].as<uint32_t>();
  messageStruct.msg = jsonMsg[STR(msg)].as<uint32_t>();
  strcpy(messageStruct.data, jsonMsg[STR(data)].as<const char*>());

  // Convert message data to json
  deserializeJson(jsonData, messageStruct.data);

  // Print message
  Serial.println(messageStruct.source);
  Serial.println(messageStruct.base_msg);
  Serial.println(messageStruct.msg);
  Serial.println(messageStruct.data);

  // Process message
  String response = ProcessRequest(jsonData, messageStruct);

  // Response data
  server.send(HTTP_OK, "application/json", response);

  tone(BUZZER_PIN, BEEP_FRE, BEEP_INCREASE_DURATION);
}

void setup() {
  Serial.begin(115200);

  // Setup WiFi
  WiFi.softAP(WIFI_SSID, WIFI_PASS, 1, 1, (uint8_t)MODULE_NAME::MAX);
  WiFi.softAPConfig(
    IPAddress(IP_ADD_1, IP_ADD_2, IP_ADD_3, IP_ADD_4),
    IPAddress(IP_ADD_1, IP_ADD_2, IP_ADD_3, IP_ADD_4),
    IPAddress(NETMASK_1, NETMASK_2, NETMASK_3, NETMASK_4));

  // Setup server
  server.on("/", HTTP_POST, OnMainServer);

  // Start server
  server.begin();
  Serial.printf("HTTP server started on port: %d\n", IP_ADD_4);

  // Setup I/O
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(MODULE_SEL_MUX_SIG, OUTPUT);

  // Lock activate module
  digitalWrite(MODULE_SEL_MUX_SIG, HIGH);
}

void loop() {
  server.handleClient();

  // Debug console
  if (Serial.available() > 0) {
    String read = Serial.readStringUntil('\n');
    StringSplitter* splitter = new StringSplitter(read, ' ', 100);

    // Select module: set <channel>
    if (splitter->getItemAtIndex(0) == "set") {
      auto channel = splitter->getItemAtIndex(1).toInt();
      SelectModule(channel);

      // Add selected module to selected module list
      if (std::find(SelectModuleInfo.listSelectedIndex.begin(), SelectModuleInfo.listSelectedIndex.end(), channel + FIRST_MODULE_OFFSET)
          == SelectModuleInfo.listSelectedIndex.end()) {
        SelectModuleInfo.listSelectedIndex.push_back(channel + FIRST_MODULE_OFFSET);
      }
    }
    // Request host data: request_host <WM number> <data>
    else if (splitter->getItemAtIndex(0) == "request_host") {
      // Create message
      data_pack_t byteData = { 0 };
      byteData.base_msg = WM_REQUEST;
      byteData.msg = splitter->getItemAtIndex(1).toInt();
      strcpy(byteData.data, splitter->getItemAtIndex(2).c_str());

      // Send and get message response
      Serial.println(SendMessageToHostTimer(byteData));
      tone(BUZZER_PIN, BEEP_FRE, BEEP_INCREASE_DURATION);
    }
    // Stop all module: stop_all <0 or 1>
    else if (splitter->getItemAtIndex(0) == "stop_all") {
      SelectModuleInfo.isStopAll = (bool)splitter->getItemAtIndex(1).toInt();
    }

    delete splitter;
  }

  // Process stop all module
  if (SelectModuleInfo.isStopAll) {
    // Get current module number from selected module list
    auto moduleNum = SelectModuleInfo.listSelectedIndex[SelectModuleInfo.currentIndex];

    // Push signal to LOW
    digitalWrite(MODULE_SEL_MUX_SIG, LOW);
    moduleSelectMux.channel(moduleNum);
  }

  delay(10);
}