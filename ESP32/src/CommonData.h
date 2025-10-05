/**
 * @brief Common data
 */

#ifndef _COMMON_DATA_H
#define _COMMON_DATA_H

#include "ArduinoJson-v7.4.1.h"
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
    extern CData<std::tuple<uint16_t, uint16_t, uint16_t>> EndlessTimeClock;
    extern CData<uint8_t> StrikeNum;
    extern CData<uint16_t> TimeCycle;
    extern CData<bool> StrikeState;
    extern CData<JsonDocument> JsonResponse;
    extern CData<bool> ModuleStatus;
    extern CData<std::string> ClientName;
#ifdef _WIN64
    extern CData<std::vector<std::string>> InputParamList;
#endif
}

namespace sys_gui // GUI read/write -> Send data to HOST
{
    extern CData<uint8_t> SuccessState;
    extern CData<uint8_t> Brightness;
    extern CData<std::unordered_map<std::string, MODULE_STATUS>> ModuleStatusMap;
}
#pragma endregion

// Allow modification
#pragma region Custom_data
extern CData<std::string> CorrectPassword;
extern CData<std::string> CurrentPassword;
#pragma endregion

void UpdateAll();

#endif // !_COMMON_DATA_H
