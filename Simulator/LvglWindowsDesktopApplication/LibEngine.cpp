/**
 * @file  LibEngine.cpp
 * @brief Library engine
 */

#include <iostream>
#include <LibEngine.h>
#include <CommonDataType.h>
#include <CommonData.h>
#include <string.h>
#include <src/misc/lv_event.h>
#include <CommonLibrary.h>


 /*
 * Function name: WireModule()
 * Brief: The body of feature wire
 */
void WireModule()
{
    /* Get common data */
    std::vector<COLOR> wireColorList = WireColorList.GetValue();
    int mumOfWire = wireColorList.size();

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
            /* ASSERT or nothing */
            break;
    }

    return;
}

/*
* Function name: ThreeWiresModule()
* Brief: Handle in case of this module has 3 wires
*/
void ThreeWiresModule()
{
    /* Get common data */
    std::vector<COLOR> wireColorList = WireColorList.GetValue();

    /* If there is no red wire, then the target is the 2nd wire */
    if (std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::RED]) == 0)
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::SECOND_WIRE);
    }
    /* If the last wire is white, let cut it */
    else if (mapColor[WIRECOLOR_TYPE::WHITE] == wireColorList.back())
    {
        CorrectWireIndex.SetValue(mapWireOrder[wireColorList.size()]);
    }
    /* If there are more than a blue-wire, let cut the-last-blue-wire */
    else if (std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::BLUE]) > 1)
    {
        for (int i = wireColorList.size() - 1; i >= 0; i--)
        {
            if (wireColorList[i] == mapColor[WIRECOLOR_TYPE::BLUE])
            {
                CorrectWireIndex.SetValue(mapWireOrder[wireColorList.size()]);
                break;
            }
        }
    }
    /* Others */
    else
    {
        CorrectWireIndex.SetValue(mapWireOrder[wireColorList.size()]);
    }

    return;
}

/*
* Function name: FourWiresModule()
* Brief: Handle in case of this module has 4 wires
*/
void FourWiresModule()
{
    /* Get common data */
    std::vector<COLOR> wireColorList = WireColorList.GetValue();
    std::string seriNumber = sys_host::SerialNum.GetValue();

    /* If there are more than a red-wire
    * and the-end-number of serial-number-string is an odd number, let cut the-last-blue-wire */
    if ((std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::RED]) > 1)
        && OddCheckAtLast(seriNumber))
    {
        for (int i = wireColorList.size() - 1; i >= 0; i--)
        {
            if (wireColorList[i] == mapColor[WIRECOLOR_TYPE::BLUE])
            {
                // The order of a wire = Index + 1
                CorrectWireIndex.SetValue(mapWireOrder[i+1]);
                break;
            }
        }
    }
    /* If the number of blue-wire is equal to 1, let cut the-first-wire */
    else if (std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::BLUE]) == 1)
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FIRST_WIRE);
    }
    /* More than a yellow-wire, let cut the-last-wire */
    else if (std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::YELLOW]) > 1)
    {
        ORDER wireOrder = wireColorList.size() - 1;
        CorrectWireIndex.SetValue(mapWireOrder[wireOrder]);
    }
    /* Others */
    else
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::SECOND_WIRE);
    }

    return;
}

/*
* Function name: FiveWiresModule()
* Brief: Handle in case of this module has 5 wires
*/
void FiveWiresModule()
{
    /* Get common data */
    std::vector<COLOR> wireColorList = WireColorList.GetValue();
    std::string seriNumber = sys_host::SerialNum.GetValue();

    /* If the-last-wire is black
    * and the-end-number of serial-number-string is an odd number, then cutting the-fourth-wire */
    if ((wireColorList[wireColorList.size() - 1] == mapColor[WIRECOLOR_TYPE::BLACK])
        && OddCheckAtLast(seriNumber))
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FOURTH_WIRE);
    }
    /* Red is 1 and yellow is more than 1 --> Then cutting the-first-wire */
    else if ((std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::RED]) == 1)
        && (std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::YELLOW]) > 1))
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FIRST_WIRE);
    }
    /* Black is zero --> then cutting the-second-wire */
    else if (std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::BLACK]) == 0)
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::SECOND_WIRE);
    }
    /* Others */
    else
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FIRST_WIRE);
    }

    return;
}


/*
* Function name: SixWiresModule()
* Brief: Handle in case of this module has 6 wires
*/
void SixWiresModule()
{
    /* Get common data */
    std::vector<COLOR> wireColorList = WireColorList.GetValue();
    std::string seriNumber = sys_host::SerialNum.GetValue();

    /* Yellow is 0 and the-end-number in serial-number-string is odd, then cutting the-third-wire */
    if ((std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::YELLOW]) == 0)
        && OddCheckAtLast(seriNumber))
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::THIRD_WIRE);
    }
    /* Red is 1 and yellow is more than 1 --> Then cutting the-first-wire */
    else if ((std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::YELLOW]) == 1)
        && (std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::WHITE]) > 1))
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FOURTH_WIRE);
    }
    else if (std::count(wireColorList.begin(), wireColorList.end(), mapColor[WIRECOLOR_TYPE::RED]) == 0)
    {
        ORDER wireOrder = wireColorList.size() - 1;
        CorrectWireIndex.SetValue(mapWireOrder[wireOrder]);
    }
    /* Others */
    else
    {
        CorrectWireIndex.SetValue(WIRE_IN_ORDER::FOURTH_WIRE);
    }

    return;
}
