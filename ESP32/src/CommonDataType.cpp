/**
 * @brief Common data type
 */

#include "CommonDataType.h"

std::unordered_map<LABEL_INDICATOR, std::string> map_LABEL_INDICATOR
{
    { LABEL_INDICATOR::SND, "SND" },
    { LABEL_INDICATOR::CLR, "CLR" },
    { LABEL_INDICATOR::CAR, "CAR" },
    { LABEL_INDICATOR::IND, "IND" },
    { LABEL_INDICATOR::FRQ, "FRQ" },
    { LABEL_INDICATOR::SIG, "SIG" },
    { LABEL_INDICATOR::NSA, "NSA" },
    { LABEL_INDICATOR::MSA, "MSA" },
    { LABEL_INDICATOR::TRN, "TRN" },
    { LABEL_INDICATOR::BOB, "BOB" },
    { LABEL_INDICATOR::FRK, "FRK" },
};

std::unordered_map<BATTERY_TYPE, std::string> map_BATTERY_TYPE
{
    { BATTERY_TYPE::AA, "AA" },
    { BATTERY_TYPE::D, "D" },
};

std::unordered_map<COMPORT_TYPE, std::string> map_COMPORT_TYPE
{
    { COMPORT_TYPE::DVID, "DVID" },
    { COMPORT_TYPE::Parallel, "Parallel" },
    { COMPORT_TYPE::PS2, "PS2" },
    { COMPORT_TYPE::RJ45, "RJ45" },
    { COMPORT_TYPE::Serial, "Serial" },
    { COMPORT_TYPE::Stereo_RCA, "Stereo_RCA" },
};
