/**
 * @brief Common service library
 */

#ifndef _COMMON_SERVICE_H
#define _COMMON_SERVICE_H

#include <cstdint>
#include "CommonDataType.h"
#include "ArduinoJson-v7.4.1.h"

void RunTimer();
void InitData();
void ProcessData();
void ProcessRequest(HWND, uint32_t, JsonDocument);
JsonDocument CommonGetRequest(uint32_t);
JsonDocument CommonGetRequestWithData(uint32_t, JsonDocument);

#endif
