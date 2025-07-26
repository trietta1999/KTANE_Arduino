/**
 * @brief Common library
 */

#include <algorithm>
#include <random>
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
std::string GenerateRandomString(uint8_t takeNum, char rootLetter)
{
    std::string outputString = "";

    // Sample string
    std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Create letter list with first root letter
    std::vector<char> listString = { rootLetter };

    // Remove root letter from sample string to ensure no duplication
    characters.erase(std::remove(characters.begin(), characters.end(), rootLetter), characters.end());

    std::mt19937 generator(rand());

    std::sample(characters.begin(), characters.end(), std::back_inserter(listString), takeNum - 1, generator);

    // Join letter list to string with "\n", except the last letter
    for (uint8_t i = 0; i < listString.size(); i++) {
        outputString.push_back(listString[i]);

        if (i < listString.size() - 1)
        {
            outputString.push_back('\n');
        }
    }

    return outputString;
}
#pragma endregion
