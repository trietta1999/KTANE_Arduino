/**
 * @brief Common library
 */

#ifndef _COMMON_LIBRARY_H
#define _COMMON_LIBRARY_H

#include "CommonDataType.h"

 // Do not delete or rename
#pragma region System_function
void Init();
void AutoUpdate();
uint8_t RandomRange(uint8_t, uint8_t);
std::string GenerateSerialNumber();
bool VowelCheck(const std::string&);
bool OddCheckAtLast(const std::string&);
bool NumberCheckInTimer(uint8_t);
#pragma endregion

// Allow modification
#pragma region Custom_function
int64_t ScaleTranslate(int64_t x, int64_t in_min, int64_t in_max, int64_t out_min, int64_t out_max);
std::pair<KNOB_DIRECTION_TYPE, int16_t> GetRotationInfo(KNOB_DIRECTION_TYPE);
std::vector<std::pair<KNOB_DIRECTION_TYPE, int16_t>>::iterator GetRotationInfoIt(KNOB_DIRECTION_TYPE);
#pragma endregion

#endif // !_COMMON_LIBRARY_H
