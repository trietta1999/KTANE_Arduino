/**
 * @brief Common data type
 */

#include "CommonDataType.h"

MAP_ENUM_STR(LABEL_INDICATOR, DEF_LABEL_INDICATOR)
MAP_ENUM_STR(BATTERY_TYPE, DEF_BATTERY_TYPE)
MAP_ENUM_STR(COMPORT_TYPE, DEF_COMPORT_TYPE)
MAP_ENUM_STR(MODULE_NAME, DEF_MODULE_NAME)

#ifdef _WIN64
MAP_ENUM_WSTR(MODULE_NAME, DEF_MODULE_NAME)
#endif

MAP_ENUM_STR(WIRECOLOR_TYPE, DEF_WIRECOLOR_TYPE)
MAP_ENUM_STR(WIRE_IN_ORDER, DEF_WIRE_IN_ORDER)

std::unordered_map<WIRECOLOR_TYPE, uint32_t> mapColor =
{
    { WIRECOLOR_TYPE::RED, 0xFF0000 },
    { WIRECOLOR_TYPE::BLUE, 0x0000FF },
    { WIRECOLOR_TYPE::BLACK, 0x000000 },
};

std::vector<std::vector<WIRE_IN_ORDER>> listRedRule = {
    { WIRE_IN_ORDER::MIN, },
    { WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::B, },
    { WIRE_IN_ORDER::A, },
    { WIRE_IN_ORDER::A, WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::B, },
    { WIRE_IN_ORDER::A, WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::A, WIRE_IN_ORDER::B, WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::A, WIRE_IN_ORDER::B, },
    { WIRE_IN_ORDER::B, },
};

std::vector<std::vector<WIRE_IN_ORDER>> listBlueRule = {
    { WIRE_IN_ORDER::MIN, },
    { WIRE_IN_ORDER::B, },
    { WIRE_IN_ORDER::A, WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::B, },
    { WIRE_IN_ORDER::A, },
    { WIRE_IN_ORDER::B, },
    { WIRE_IN_ORDER::B, WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::A, WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::A, },
};

std::vector<std::vector<WIRE_IN_ORDER>> listBlackRule = {
    { WIRE_IN_ORDER::MIN, },
    { WIRE_IN_ORDER::A, WIRE_IN_ORDER::B, WIRE_IN_ORDER::C},
    { WIRE_IN_ORDER::A, WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::B, },
    { WIRE_IN_ORDER::A, WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::B, },
    { WIRE_IN_ORDER::B, WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::A, WIRE_IN_ORDER::B, },
    { WIRE_IN_ORDER::C, },
    { WIRE_IN_ORDER::C, },
};

std::unordered_map<WIRECOLOR_TYPE, std::vector<std::vector<WIRE_IN_ORDER>>> mapColorRule = {
    { WIRECOLOR_TYPE::RED, listRedRule },
    { WIRECOLOR_TYPE::BLUE, listBlueRule },
    { WIRECOLOR_TYPE::BLACK, listBlackRule },
};
