/**
 * @brief Common library
 */

#include <algorithm>
#include "CommonLibrary.h"
#include "CommonData.h"

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
void CreateRandomWireList()
{
    // Create random wire list and color
    uint8_t wireNum = RandomRange(3, 7);

    std::vector<COLOR> listColor;
    for (uint8_t i = 0; i < wireNum; i++)
    {
        uint8_t randomColorIndex = RandomRange((uint8_t)WIRECOLOR_TYPE::MIN + 1, (uint8_t)WIRECOLOR_TYPE::MAX) - 1;

        /*
        @Brief
        1. mapColor.begin() => Returns an iterator pointing to the first element in the unordered_map
        2. std::next(mapColor.begin(), randomColorIndex) => move the iterator to the position by [randomColorIndex] unit from the first iterator
        3. ->second => accesses the value (not the key) at that iterator position
        */

        COLOR getColorByKey = std::next(mapColor.begin(), randomColorIndex)->second;
        listColor.push_back(getColorByKey);
    }
    if (listColor.size() < 6)
    {
        listColor.resize(6, NON_COLOR);
    }

    WireColorList.SetValue(listColor);
}
#pragma endregion
