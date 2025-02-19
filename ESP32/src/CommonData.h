/**
 * @brief Common data
 */

#ifndef _COMMON_DATA_H
#define _COMMON_DATA_H

#ifdef _WIN64
#include <cstdint>
#endif
#include "CData.h"
#include "CommonDataType.h"

/* TODO: Declare shared data for the system
         Use "extern" and do not declare initial values
*/

// Do not modify
#pragma region System_data
#pragma region Read_only
extern CData<LABEL_INDICATOR> LabelIndicator;
extern CData<BATTERY_TYPE> BatteryType;
extern CData<COMPORT_TYPE> ComPortType;
extern CData<String_t> SerialNum;
extern CData<uint8_t> BatteryNum;
extern CData<String_t> TimeClock;
extern CData<uint8_t> StrikeNum;
extern CData<bool> StrikeState_GUI;
extern CData<bool> StrikeState_HARD;
#pragma endregion

#pragma region Read_Write
extern CData<bool> IsSuccess;
#pragma endregion

#pragma endregion

// Allow modification
#pragma region Custom_data
extern CData<uint16_t> Button2Value;
extern CData<int32_t> SliderValue;
extern CData<int32_t> ArcValue;
extern CData<uint16_t> CheckboxValue;
extern CData<String_t> DropdownValue;
extern CData<uint16_t> SwitchValue;
extern CData<String_t> RollerValue;
#pragma endregion

#endif // !_COMMON_DATA_H
