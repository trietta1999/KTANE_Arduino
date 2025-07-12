/**
 * @brief Common library
 */

#include <algorithm>
#include <iterator>
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
std::tuple<TEXT_DISPLAY, uint8_t> GetRandomTextDisplay()
{
    auto textDisplay = (TEXT_DISPLAY)RandomRange(((uint8_t)TEXT_DISPLAY::MIN) + 1, (uint8_t)TEXT_DISPLAY::MAX);
    auto focusPos = std::get<FOCUSPOS_POS>(map_TextDisplayWithFocusPostion[textDisplay]);

    return std::make_tuple(textDisplay, focusPos);
}

std::vector<TEXT_LABEL> GetTextLabelListFromMap(uint8_t takeNum)
{
    // Convert map to text label list
    std::vector<TEXT_LABEL> listTextLabel = { };
    std::transform(map_TextLabel.begin(), map_TextLabel.end(),
        std::back_inserter(listTextLabel),
        [](const auto& pair) { return pair.first; });

    // Get list text label
    auto textLabel = (TEXT_LABEL)RandomRange(((uint8_t)TEXT_LABEL::MIN) + 1, (uint8_t)TEXT_LABEL::MAX);
    auto listTextLabelItem = map_TextLabelList[textLabel];

    // Take [takeNum] element trong list text label
    auto randomIndex = RandomRange(0, listTextLabelItem.size() - takeNum);
    std::vector<TEXT_LABEL> listSelectTextLabel(listTextLabelItem.begin() + randomIndex, (listTextLabelItem.begin() + randomIndex) + takeNum);

    return listSelectTextLabel;
}

TEXT_LABEL SetCorrectTextLabel(uint8_t position, std::vector<TEXT_LABEL> listTextLabel)
{
    auto textLabel = listTextLabel[position - 1];
    auto targetListTextLabel = map_TextLabelList[textLabel];

    // Check first mapping text label in map label in
    for (const auto& targetTextLabel : targetListTextLabel)
    {
        for (const auto& i_textLabel : listTextLabel)
        {
            if (i_textLabel == targetTextLabel)
            {
                return i_textLabel;
            }
        }
    }

    return TEXT_LABEL::MIN;
}
#pragma endregion
