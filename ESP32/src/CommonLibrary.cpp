/**
 * @brief Common library
 */

#include <algorithm>
#include <random>
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
std::vector<bool> CreateRandomWireEnableList(uint8_t size)
{
    std::vector<bool> sample(size);

    // Get number of True value
    uint8_t trueCount = RandomRange(WIRE_NUM_MIN, WIRE_NUM_MAX + 1);

    // Assign True value to first element range
    for (uint8_t i = 0; i < trueCount; i++) {
        sample[i] = true;
    }

    std::mt19937 gen(rand());
    std::shuffle(sample.begin(), sample.end(), gen); // Random shuffle

    return sample;
}

std::vector<WIRECOLOR_TYPE> CreateRandomWireColorList(std::vector<bool> enableList)
{
    uint8_t tempIndex = 0;
    auto colorList = WireColorList.GetValue();
    std::vector<WIRECOLOR_TYPE> sample(enableList.size());

    for (uint8_t i = 0; i < enableList.size(); i++)
    {
        // Position is visible
        if (enableList[i])
        {
            WIRECOLOR_TYPE color = WIRECOLOR_TYPE::MIN;

            // Get random color
            do
            {
                color = (WIRECOLOR_TYPE)RandomRange((uint8_t)WIRECOLOR_TYPE::MIN + 1, (uint8_t)WIRECOLOR_TYPE::MAX);
            } while (sample[tempIndex] == color); // Color must not be same with previous color

            // Set latest color index
            tempIndex = i;

            // Update color list
            sample[i] = color;
            colorList.push_back(color);
        }
    }

    WireColorList.SetValue(colorList);

    return sample;
}
#pragma endregion
