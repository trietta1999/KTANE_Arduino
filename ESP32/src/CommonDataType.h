/**
 * @brief Common data type
 */

#ifndef _COMMON_DATATYPE_H
#define _COMMON_DATATYPE_H

#include <string>

 // Do not modify
#pragma region System_datatype
enum class LABEL_INDICATOR
{
    SND,
    CLR,
    CAR,
    IND,
    FRQ,
    SIG,
    NSA,
    MSA,
    TRN,
    BOB,
    FRK,
};

enum class BATTERY_TYPE
{
    AA,
    D,
};

enum class COMPORT_TYPE
{
    DVID,
    Parallel,
    PS2,
    RJ45,
    Serial,
    Stereo_RCA,
};

enum class LED_COLOR
{
    Red,
    Green,
};
#pragma endregion

// Allow modification
#pragma region Custom_datatype

#pragma endregion

#endif // !_COMMON_DATATYPE_H
