/**
 * @brief Common library
 */

#include <algorithm>
#include <random>
#include <iterator>
#include <numeric>
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
bool StageModule(uint8_t displayNum, std::array<uint8_t, BUTTON_NUM> listValue)
{
    auto stage = CurrentStage.GetValue();
    CurrentCorrectData.SetValue(std::make_pair(POSTION_TYPE::INVALID, INCORRECT));

    switch (stage)
    {
    case 1:
        return Stage1Module(displayNum, listValue);
        break;

    case 2:
        return Stage2Module(displayNum, listValue);
        break;

    case 3:
        return Stage3Module(displayNum, listValue);
        break;

    case 4:
        return Stage4Module(displayNum, listValue);
        break;

    case 5:
        return Stage5Module(displayNum, listValue);
        break;

    default:
        return false;
    }
}

bool Stage1Module(uint8_t displayNum, std::array<uint8_t, BUTTON_NUM> listValue)
{
    bool result = false;

    switch (displayNum)
    {
        // If the display is 1, press the button in the second position
    case 1:
        // If the display is 2, press the button in the second position
    case 2:
    {
        CurrentCorrectData.SetValue(std::make_pair(POSTION_TYPE::SECOND, listValue[(uint8_t)POSTION_TYPE::SECOND]));
        result = true;
    }
    break;

    // If the display is 3, press the button in the third position
    case 3:
    {
        CurrentCorrectData.SetValue(std::make_pair(POSTION_TYPE::THIRD, listValue[(uint8_t)POSTION_TYPE::THIRD]));
        result = true;
    }
    break;

    // If the display is 4, press the button in the fourth position
    case 4:
    {
        CurrentCorrectData.SetValue(std::make_pair(POSTION_TYPE::FOURTH, listValue[(uint8_t)POSTION_TYPE::FOURTH]));
        result = true;
    }
    break;

    default:
        break;
    }

    return result;
}

bool Stage2Module(uint8_t displayNum, std::array<uint8_t, BUTTON_NUM> listValue)
{
    bool result = false;
    auto listStageData = ListStageData.GetValue();

    switch (displayNum)
    {
        // If the display is 1, press the button labeled "4".
    case 1:
    {
        auto index = std::find(listValue.begin(), listValue.end(), 4) - listValue.begin();

        if (index < listValue.size())
        {
            CurrentCorrectData.SetValue(std::make_pair((POSTION_TYPE)index, 4));
            result = true;
        }
    }
    break;

    // If the display is 2, press the button in the same position as you pressed in stage 1.
    case 2:
    {
        auto stage1ButtonPos = std::get<POSITION_POS>(listStageData[0]);
        CurrentCorrectData.SetValue(std::make_pair(stage1ButtonPos, listValue[(uint8_t)stage1ButtonPos]));
        result = true;
    }
    break;

    // If the display is 3, press the button in the first position.
    case 3:
    {
        CurrentCorrectData.SetValue(std::make_pair(POSTION_TYPE::FIRST, listValue[(uint8_t)POSTION_TYPE::FIRST]));
        result = true;
    }
    break;

    // If the display is 4, press the button in the same position as you pressed in stage 1.
    case 4:
    {
        auto stage1ButtonPos = std::get<POSITION_POS>(listStageData[0]);
        CurrentCorrectData.SetValue(std::make_pair(stage1ButtonPos, listValue[(uint8_t)stage1ButtonPos]));
        result = true;
    }
    break;

    default:
        break;
    }

    return result;
}

bool Stage3Module(uint8_t displayNum, std::array<uint8_t, BUTTON_NUM> listValue)
{
    bool result = false;
    auto listStageData = ListStageData.GetValue();

    switch (displayNum)
    {
        // If the display is 1, press the button with the same label you pressed in stage 2.
    case 1:
    {
        auto stageData = listStageData[1];
        auto index = std::find(listValue.begin(), listValue.end(), std::get<VALUE_POS>(stageData)) - listValue.begin();

        if (index < listValue.size())
        {
            CurrentCorrectData.SetValue(std::make_pair((POSTION_TYPE)index, std::get<VALUE_POS>(stageData)));
            result = true;
        }
    }
    break;

    // If the display is 2, press the button with the same label you pressed in stage 1.
    case 2:
    {
        auto stageData = listStageData[0];
        auto index = std::find(listValue.begin(), listValue.end(), std::get<VALUE_POS>(stageData)) - listValue.begin();

        if (index < listValue.size())
        {
            CurrentCorrectData.SetValue(std::make_pair((POSTION_TYPE)index, std::get<VALUE_POS>(stageData)));
            result = true;
        }
    }
    break;

    // If the display is 3, press the button in the third position.
    case 3:
    {
        CurrentCorrectData.SetValue(std::make_pair(POSTION_TYPE::THIRD, listValue[(uint8_t)POSTION_TYPE::THIRD]));
        result = true;
    }
    break;

    // If the display is 4, press the button labeled "4".
    case 4:
    {
        auto index = std::find(listValue.begin(), listValue.end(), 4) - listValue.begin();

        if (index < listValue.size())
        {
            CurrentCorrectData.SetValue(std::make_pair((POSTION_TYPE)index, 4));
            result = true;
        }
    }
    break;

    default:
        break;
    }

    return result;
}

bool Stage4Module(uint8_t displayNum, std::array<uint8_t, BUTTON_NUM> listValue)
{
    bool result = false;
    auto listStageData = ListStageData.GetValue();

    switch (displayNum)
    {
        // If the display is 1, press the button in the same position as you pressed in stage 1.
    case 1:
    {
        auto stage1ButtonPos = std::get<POSITION_POS>(listStageData[0]);
        CurrentCorrectData.SetValue(std::make_pair(stage1ButtonPos, listValue[(uint8_t)stage1ButtonPos]));
        result = true;
    }
    break;

    // If the display is 2, press the button in the first position.
    case 2:
    {
        CurrentCorrectData.SetValue(std::make_pair(POSTION_TYPE::FIRST, listValue[(uint8_t)POSTION_TYPE::FIRST]));
        result = true;
    }
    break;

    // If the display is 3, press the button in the same position as you pressed in stage 2.
    case 3:
        // If the display is 4, press the button in the same position as you pressed in stage 2.
    case 4:
    {
        auto stage2ButtonPos = std::get<POSITION_POS>(listStageData[1]);
        CurrentCorrectData.SetValue(std::make_pair(stage2ButtonPos, listValue[(uint8_t)stage2ButtonPos]));
        result = true;
    }
    break;

    default:
        break;
    }

    return result;
}

bool Stage5Module(uint8_t displayNum, std::array<uint8_t, BUTTON_NUM> listValue)
{
    bool result = false;
    auto listStageData = ListStageData.GetValue();

    switch (displayNum)
    {
        // If the display is 1, press the button with the same label you pressed in stage 1.
    case 1:
    {
        auto stageData = listStageData[0];
        auto index = std::find(listValue.begin(), listValue.end(), std::get<VALUE_POS>(stageData)) - listValue.begin();

        if (index < listValue.size())
        {
            CurrentCorrectData.SetValue(std::make_pair((POSTION_TYPE)index, std::get<VALUE_POS>(stageData)));
            result = true;
        }
    }
    break;

    // If the display is 2, press the button with the same label you pressed in stage 2.
    case 2:
    {
        auto stageData = listStageData[1];
        auto index = std::find(listValue.begin(), listValue.end(), std::get<VALUE_POS>(stageData)) - listValue.begin();

        if (index < listValue.size())
        {
            CurrentCorrectData.SetValue(std::make_pair((POSTION_TYPE)index, std::get<VALUE_POS>(stageData)));
            result = true;
        }
    }
    break;

    // If the display is 3, press the button with the same label you pressed in stage 4.
    case 3:
    {
        auto stageData = listStageData[3];
        auto index = std::find(listValue.begin(), listValue.end(), std::get<VALUE_POS>(stageData)) - listValue.begin();

        if (index < listValue.size())
        {
            CurrentCorrectData.SetValue(std::make_pair((POSTION_TYPE)index, std::get<VALUE_POS>(stageData)));
            result = true;
        }
    }
    break;

    // If the display is 4, press the button with the same label you pressed in stage 3.
    case 4:
    {
        auto stageData = listStageData[2];
        auto index = std::find(listValue.begin(), listValue.end(), std::get<VALUE_POS>(stageData)) - listValue.begin();

        if (index < listValue.size())
        {
            CurrentCorrectData.SetValue(std::make_pair((POSTION_TYPE)index, std::get<VALUE_POS>(stageData)));
            result = true;
        }
    }
    break;

    default:
        break;
    }

    return result;
}

std::array<uint8_t, BUTTON_NUM> GenerateArrayNumber()
{
    std::vector<uint8_t> rangeNum(9);
    std::vector<uint8_t> vecResult;
    std::array<uint8_t, BUTTON_NUM> arrResult;

    std::iota(rangeNum.begin(), rangeNum.end(), 1);

    std::mt19937 generator(rand());

    std::sample(rangeNum.begin(), rangeNum.end(), std::back_inserter(vecResult), BUTTON_NUM, generator);

    std::copy(vecResult.begin(), vecResult.end(), arrResult.begin());

    return arrResult;
}
#pragma endregion
