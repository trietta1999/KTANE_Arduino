/**
 * @brief Common hardware library
 */

#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#ifndef _WIN64
#include "src/CommonDataType.h"
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

namespace serial {
void Setup() {
  Serial.begin(9600);
}

void SendMessage(const char* target, uint32_t base_msg, uint32_t msg, const char* data) {
  if (data) {
    Serial.println(DATA_HEADER + target + "|" + base_msg + "|" + msg + "|" + data + DATA_TRAILER);
    SerialBT.println(DATA_HEADER + target + "|" + base_msg + "|" + msg + "|" + data + DATA_TRAILER);
  } else {
    Serial.println(DATA_HEADER + target + "|" + base_msg + "|" + msg + DATA_TRAILER);
    SerialBT.println(DATA_HEADER + target + "|" + base_msg + "|" + msg + DATA_TRAILER);
  }
}
}

namespace ble {
void Setup() {
  SerialBT.begin(CLIENT_NAME);
}
}
#endif
#endif
