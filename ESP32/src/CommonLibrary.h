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
std::tuple<TEXT_DISPLAY, uint8_t> GetRandomTextDisplay();
std::vector<TEXT_LABEL> GetTextLabelListFromMap(uint8_t);
TEXT_LABEL SetCorrectTextLabel(uint8_t, std::vector<TEXT_LABEL>);
#pragma endregion

#endif // !_COMMON_LIBRARY_H
