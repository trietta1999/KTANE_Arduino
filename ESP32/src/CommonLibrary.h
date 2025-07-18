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
std::tuple<TEXT_TYPE, std::string> GetRandomText();
std::vector<int32_t> FlatMorseCodeArray(std::vector<std::array<int32_t, MAX_MORSE_SYMBOL>>);
std::array<int32_t, MAX_MORSE_SYMBOL> ConvertSymbolToDigitArray(std::string);
std::vector<std::array<int32_t, MAX_MORSE_SYMBOL>> ConvertTextToMorseCode(std::string);
#pragma endregion

#endif // !_COMMON_LIBRARY_H
