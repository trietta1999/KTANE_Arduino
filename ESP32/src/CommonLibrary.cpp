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

/*
 * Function name: WireModule()
 * Brief: The body of feature wire
 */
void WireModule()
{
    /* Get common data */
    auto mumOfWire = WireColorList.GetValue().size();

    switch (mumOfWire)
    {
    case 3:
    {
        ThreeWiresModule();
    }
    break;

    case 4:
    {
        FourWiresModule();
    }
    break;

    case 5:
    {
        FiveWiresModule();
    }
    break;

    case 6:
    {
        SixWiresModule();
    }
    break;

    default:
        break;
    }
}

/*
* Function name: ThreeWiresModule()
* Brief: Handle in case of this module has 3 wires
*/
void ThreeWiresModule()
{
    /* Get common data */
    auto wireColorList = WireColorList.GetValue();

    /* If there is no red wire, then the target is the 2nd wire */
    if (CountElementOccurences(wireColorList, WIRECOLOR_TYPE::RED) == 0)
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::SECOND_WIRE);
    }
    /* If the last wire is white, let cut it */
    else if (WIRECOLOR_TYPE::WHITE == wireColorList.back())
    {
        CorrectWireIndex.SetValue((WIRE_IN_ORDER)wireColorList.size());
    }
    /* If there are more than a blue-wire, let cut the-last-blue-wire */
    else if (CountElementOccurences(wireColorList, WIRECOLOR_TYPE::BLUE) > 1)
    {
        for (int8_t i = wireColorList.size() - 1; i >= 0; i--)
        {
            if (wireColorList[i] == WIRECOLOR_TYPE::BLUE)
            {
                CorrectWireIndex.SetValue((WIRE_IN_ORDER)(i + 1));
                break;
            }
        }
    }
    /* Others */
    else
    {
        CorrectWireIndex.SetValue((WIRE_IN_ORDER)wireColorList.size());
    }
}

/*
* Function name: FourWiresModule()
* Brief: Handle in case of this module has 4 wires
*/
void FourWiresModule()
{
    /* Get common data */
    auto wireColorList = WireColorList.GetValue();
    std::string seriNumber = sys_host::SerialNum.GetValue();

    /* If there are more than a red-wire
    * and the-end-number of serial-number-string is an odd number, let cut the-last-blue-wire */
    if ((CountElementOccurences(wireColorList, WIRECOLOR_TYPE::RED) > 1) && OddCheckAtLast(seriNumber))
    {
        for (int8_t i = wireColorList.size() - 1; i >= 0; i--)
        {
            if (wireColorList[i] == WIRECOLOR_TYPE::RED)
            {
                // The order of a wire = Index + 1
                CorrectWireIndex.SetValue((WIRE_IN_ORDER)(i + 1));
                break;
            }
        }
    }
    /* If the number of blue-wire is equal to 1, let cut the-first-wire */
    else if (CountElementOccurences(wireColorList, WIRECOLOR_TYPE::BLUE) == 1)
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FIRST_WIRE);
    }
    /* More than a yellow-wire, let cut the-last-wire */
    else if (CountElementOccurences(wireColorList, WIRECOLOR_TYPE::YELLOW) > 1)
    {
        CorrectWireIndex.SetValue((WIRE_IN_ORDER)wireColorList.size());
    }
    /* Others */
    else
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::SECOND_WIRE);
    }
}

/*
* Function name: FiveWiresModule()
* Brief: Handle in case of this module has 5 wires
*/
void FiveWiresModule()
{
    /* Get common data */
    auto wireColorList = WireColorList.GetValue();
    std::string seriNumber = sys_host::SerialNum.GetValue();

    /* If the-last-wire is black
    * and the-end-number of serial-number-string is an odd number, then cutting the-fourth-wire */
    if ((wireColorList.back() == WIRECOLOR_TYPE::BLACK) && OddCheckAtLast(seriNumber))
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FOURTH_WIRE);
    }
    /* Red is 1 and yellow is more than 1 --> Then cutting the-first-wire */
    else if ((CountElementOccurences(wireColorList, WIRECOLOR_TYPE::RED) == 1) && (CountElementOccurences(wireColorList, WIRECOLOR_TYPE::YELLOW) > 1))
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FIRST_WIRE);
    }
    /* Black is zero --> then cutting the-second-wire */
    else if (CountElementOccurences(wireColorList, WIRECOLOR_TYPE::BLACK) == 0)
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::SECOND_WIRE);
    }
    /* Others */
    else
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FIRST_WIRE);
    }
}

/*
* Function name: SixWiresModule()
* Brief: Handle in case of this module has 6 wires
*/
void SixWiresModule()
{
    /* Get common data */
    auto wireColorList = WireColorList.GetValue();
    std::string seriNumber = sys_host::SerialNum.GetValue();

    /* Yellow is 0 and the-end-number in serial-number-string is odd, then cutting the-third-wire */
    if ((CountElementOccurences(wireColorList, WIRECOLOR_TYPE::YELLOW) == 0) && OddCheckAtLast(seriNumber))
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::THIRD_WIRE);
    }
    /* Red is 1 and yellow is more than 1 --> Then cutting the-first-wire */
    else if ((CountElementOccurences(wireColorList, WIRECOLOR_TYPE::YELLOW) == 1) && (CountElementOccurences(wireColorList, WIRECOLOR_TYPE::WHITE) > 1))
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FOURTH_WIRE);
    }
    else if (CountElementOccurences(wireColorList, WIRECOLOR_TYPE::RED) == 0)
    {
        CorrectWireIndex.SetValue((WIRE_IN_ORDER)wireColorList.size());
    }
    /* Others */
    else
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FOURTH_WIRE);
    }
}

uint8_t CountElementOccurences(std::vector<WIRECOLOR_TYPE> wireColorList, WIRECOLOR_TYPE color)
{
    return std::count(wireColorList.begin(), wireColorList.end(), color);
}
#pragma endregion
