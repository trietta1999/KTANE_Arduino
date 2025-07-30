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

MAP_ENUM_STR(KNOB_DIRECTION_TYPE, DEF_KNOB_DIRECTION_TYPE)

std::vector<std::pair<KNOB_DIRECTION_TYPE, int16_t>> listKnobDirectionTypeRotation = {
    { KNOB_DIRECTION_TYPE::UP, 0 },
    { KNOB_DIRECTION_TYPE::RIGHT, 900 },
    { KNOB_DIRECTION_TYPE::DOWN, 1800 },
    { KNOB_DIRECTION_TYPE::LEFT, -900 },
};

std::unordered_map<KNOB_DIRECTION_TYPE, std::vector<led_pattern_t>> mapLedPattern = {
    {
        KNOB_DIRECTION_TYPE::UP,
        {
            {
                { L_OFF, L_OFF, L_ON, },
                { L_ON, L_ON, L_ON, },
                { L_OFF, L_ON, L_ON, },
                { L_ON, L_OFF, L_ON, },
            },
            {
                { L_ON, L_OFF, L_ON, },
                { L_OFF, L_ON, L_ON, },
                { L_OFF, L_ON, L_OFF, },
                { L_OFF, L_ON, L_ON, },
            }
        }
    },
    {
        KNOB_DIRECTION_TYPE::DOWN,
        {
            {
                { L_OFF, L_ON, L_ON, },
                { L_ON, L_ON, L_ON, },
                { L_OFF, L_OFF, L_ON, },
                { L_ON, L_OFF, L_ON, },
            },
            {
                { L_ON, L_OFF, L_ON, },
                { L_OFF, L_ON, L_OFF, },
                { L_OFF, L_ON, L_OFF, },
                { L_OFF, L_OFF, L_ON, },
            }
        }
    },
    {
        KNOB_DIRECTION_TYPE::LEFT,
        {
            {
                { L_OFF, L_OFF, L_OFF, },
                { L_ON, L_OFF, L_OFF, },
                { L_OFF, L_ON, L_OFF, },
                { L_ON, L_ON, L_ON, },
            },
            {
                { L_OFF, L_OFF, L_OFF, },
                { L_OFF, L_OFF, L_OFF, },
                { L_OFF, L_ON, L_OFF, },
                { L_ON, L_ON, L_OFF, },
            }
        }
    },
    {
        KNOB_DIRECTION_TYPE::RIGHT,
        {
            {
                { L_ON, L_OFF, L_ON, },
                { L_ON, L_ON, L_ON, },
                { L_ON, L_ON, L_ON, },
                { L_OFF, L_ON, L_OFF, },
            },
            {
                { L_ON, L_OFF, L_ON, },
                { L_ON, L_ON, L_ON, },
                { L_ON, L_OFF, L_OFF, },
                { L_OFF, L_ON, L_OFF, },
            }
        }
    },
};
