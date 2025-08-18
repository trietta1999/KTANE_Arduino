/**
 * @brief Common service library
 */

#ifndef _COMMON_SERVICE_H
#define _COMMON_SERVICE_H

#include <cstdint>
#include "CommonDataType.h"
#include "ArduinoJson-v7.4.1.h"

void InitData();
void ProcessData();
JsonDocument ProcessRequest(HWND, uint32_t, JsonDocument);
JsonDocument CommonSendRequest(uint32_t);
JsonDocument CommonSendRequestWithData(uint32_t, JsonDocument);

#endif
