/**
 * @brief Common data
 */

#ifndef _COMMON_DATA_H
#define _COMMON_DATA_H

#ifdef _WIN64
#include "ArduinoJson-v7.4.1.h"
#endif
#include "CommonDataType.h"
#include "CData.h"

 /* TODO: Declare shared data for the system
          Use "extern" and do not declare initial values
 */

 // Do not modify
#pragma region System_data
namespace sys_host // GUI read only, received from HOST
{
    extern CData<LABEL_INDICATOR> LabelIndicator;
    extern CData<BATTERY_TYPE> BatteryType;
    extern CData<COMPORT_TYPE> ComPortType;
    extern CData<std::string> SerialNum;
    extern CData<uint8_t> BatteryNum;
    extern CData<uint32_t> RandomSeed;
    extern CData<std::pair<uint8_t, uint8_t>> TimeClock;
    extern CData<uint8_t> StrikeNum;
    extern CData<uint16_t> TimeCycle;
    extern CData<bool> StrikeState;
    extern CData<bool> TimeOut;
#ifdef _WIN64
    extern CData<JsonDocument> JsonResponse;
#endif
}

namespace sys_gui // GUI read/write -> Send data to HOST
{
    extern CData<uint8_t> SuccessState;
    extern CData<uint8_t> Brightness;
    extern CData<bool> IsStarted;
    extern CData<std::unordered_map<std::string, MODULE_STATUS>> ModuleStatusMap;
}
#pragma endregion

// Allow modification
#pragma region Custom_data

#pragma endregion

void UpdateAll();

#endif // !_COMMON_DATA_H
