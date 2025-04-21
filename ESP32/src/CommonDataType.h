/**
 * @brief Common data type
 */

#ifndef _COMMON_DATATYPE_H
#define _COMMON_DATATYPE_H

#include <string>
#include <unordered_map>

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
    MAX
};
extern std::unordered_map<LABEL_INDICATOR, std::string> map_LABEL_INDICATOR;

enum class BATTERY_TYPE
{
    AA,
    D,
    MAX
};
extern std::unordered_map<BATTERY_TYPE, std::string> map_BATTERY_TYPE;

enum class COMPORT_TYPE
{
    DVID,
    Parallel,
    PS2,
    RJ45,
    Serial,
    Stereo_RCA,
    MAX
};
extern std::unordered_map<COMPORT_TYPE, std::string> map_COMPORT_TYPE;

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
