/**
 * @brief Common library
 */

#include <algorithm>
#include "CommonLibrary.h"
#include "CommonData.h"
#include "CommonService.h"

 // Do not delete or rename
#pragma region System_function
uint8_t RandomRange(uint8_t a, uint8_t b)
{
    return a + rand() % (b - a);
}

std::string GenerateSerialNumber() {
    uint8_t total = 10;
    std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string digits = "0123456789";
    std::string serial_number;

    for (uint8_t i = 0; i < total - 1; i++) {
        uint8_t random_index = RandomRange(0, characters.size());
        serial_number += characters[random_index];
    }

    uint8_t random_index = RandomRange(0, digits.size());
    serial_number += digits[random_index];

    return serial_number;
}

bool VowelCheck(const std::string& str)
{
    std::vector<char> vowels = { 'A', 'I','E','O','U' };
    for (const auto& chr : str)
    {
        if (std::find(vowels.begin(), vowels.end(), chr) != vowels.end())
        {
            return true;
        }
    }

    return false;
}

bool OddCheckAtLast(const std::string& str)
{
    if ((str.back() - '0') % 2 == 1)
    {
        return true;
    }

    return false;
}

bool NumberCheckInTimer(uint8_t num)
{
    auto timer = sys_host::TimeClock.GetValue();
    uint8_t minute = std::get<MINUTE_POS>(timer);
    uint8_t second = std::get<SECOND_POS>(timer);

    if ((minute / 10 % 10 == num) || (minute % 10 == num) || (second / 10 % 10 == num) || (second % 10 == num))
    {
        return true;
    }

    return false;
}
#pragma endregion

// Allow modification
#pragma region Custom_function
std::tuple<TEXT_TYPE, std::string> GetRandomText()
{
    auto textType = (TEXT_TYPE)RandomRange(((uint8_t)TEXT_TYPE::MIN) + 1, (uint8_t)TEXT_TYPE::MAX);
    auto textStr = map_TEXT_TYPE[textType];

    return std::make_tuple(textType, textStr);
}

std::vector<int32_t> FlatMorseCodeArray(std::vector<std::array<int32_t, MAX_MORSE_SYMBOL>> list)
{
    std::vector<int32_t> flat = { };

    // Insert each sub-array to end of vector
    for (const auto& morseCode : list)
    {
        flat.insert(flat.end(), morseCode.begin(), morseCode.end());
    }

    return flat;
}

std::array<int32_t, MAX_MORSE_SYMBOL> ConvertSymbolToDigitArray(std::string pattern)
{
    std::array<int32_t, MAX_MORSE_SYMBOL> morseCode = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };

    // Fill morse symbol to array
    for (uint8_t i = 0; i < pattern.length(); i++)
    {
        if (pattern[i] == DOT_CHAR)
        {
            morseCode[i] = DOT_LEVEL;
        }
        else
        {
            morseCode[i] = DASH_LEVEL;
        }
    }

    return morseCode;
}

std::vector<std::array<int32_t, MAX_MORSE_SYMBOL>> ConvertTextToMorseCode(std::string textStr)
{
    std::vector<std::array<int32_t, MAX_MORSE_SYMBOL>> listMorseCode = { };

    for (const auto& strChar : textStr)
    {
        // Get morse code of letter
        auto pattern = mapLetterMorsePattern[strChar];
        auto morseCode = ConvertSymbolToDigitArray(pattern);

        // Push morse code of letter to vector 
        listMorseCode.push_back(morseCode);
    }

#ifndef UNIT_TEST
    // Auto fill empty morse code
    if (listMorseCode.size() < MAX_LETTER)
    {
        for (uint8_t i = 0; i < MAX_LETTER - listMorseCode.size(); i++)
        {
            listMorseCode.push_back({ SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL });
        }
    }
#endif

    return listMorseCode;
}
#pragma endregion
