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
    std::vector<WIRECOLOR_TYPE> listColor;
    uint8_t wireNum = RandomRange(MIN_WIRE_NUM, MAX_WRIRE_NUM + 1);

    for (uint8_t i = 0; i < wireNum; i++)
    {
        auto randomColorType = (WIRECOLOR_TYPE)RandomRange((uint8_t)WIRECOLOR_TYPE::MIN + 1, (uint8_t)WIRECOLOR_TYPE::MAX);
        listColor.push_back(randomColorType);
    }

    WireColorList.SetValue(listColor);
}

// Solution referd to https://ktane.fandom.com/wiki/Complicated_Wires#Optimized_(LeGeND/Lebossle)
void CheckWire(wire_t& wire)
{
    // Check both 2 colors
    if ((wire.color1 != WIRECOLOR_TYPE::MIN) && (wire.color2 != WIRECOLOR_TYPE::MIN))
    {
        if (wire.led && wire.star)
        {
            wire.canCut = false;
        }
        else if (wire.star)
        {
            if (sys_host::ComPortType.GetValue() == COMPORT_TYPE::Parallel)
            {
                wire.canCut = true;
            }
        }
        // Led is ON
        // or
        // Both led and star are OFF
        else
        {
            if (!OddCheckAtLast(sys_host::SerialNum.GetValue()))
            {
                wire.canCut = true;
            }
        }
    }
    else if ((wire.color1 == WIRECOLOR_TYPE::WHITE) || (wire.color2 == WIRECOLOR_TYPE::WHITE))
    {
        if (wire.led && wire.star)
        {
            if (sys_host::BatteryNum.GetValue() >= 2)
            {
                wire.canCut = true;
            }
        }
        else if (wire.led)
        {
            wire.canCut = false;
        }
        // Star is ON
        // or
        // Both led and star is OFF
        else
        {
            wire.canCut = true;
        }
    }
    else if ((wire.color1 == WIRECOLOR_TYPE::RED) || (wire.color2 == WIRECOLOR_TYPE::RED))
    {
        if (wire.led)
        {
            if (sys_host::BatteryNum.GetValue() >= 2)
            {
                wire.canCut = true;
            }
        }
        else if (wire.star)
        {
            wire.canCut = true;
        }
        // Both led and star is OFF
        else
        {
            if (!OddCheckAtLast(sys_host::SerialNum.GetValue()))
            {
                wire.canCut = true;
            }
        }
    }
    else if ((wire.color1 == WIRECOLOR_TYPE::BLUE) || (wire.color2 == WIRECOLOR_TYPE::BLUE))
    {
        if (wire.led)
        {
            if (sys_host::ComPortType.GetValue() == COMPORT_TYPE::Parallel)
            {
                wire.canCut = true;
            }
        }
        else if (wire.star)
        {
            wire.canCut = false;
        }
        // Both led and star is OFF
        else
        {
            if (!OddCheckAtLast(sys_host::SerialNum.GetValue()))
            {
                wire.canCut = true;
            }
        }
    }
}

#pragma endregion
