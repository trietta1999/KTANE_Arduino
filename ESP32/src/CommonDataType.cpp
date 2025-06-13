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

MAP_ENUM_STR(COLOR_TYPE, DEF_COLOR_TYPE)

/* Color map
   Refer [On the Subject of Simon Says] */
std::unordered_map<const char*, std::unordered_map<COLOR_TYPE, std::unordered_map<uint8_t, COLOR_TYPE>>> mapColorSequence = {
    // Table 1: If the serial number contains a vowel
    {
        WITH_VOWEL,
        {
            {
                COLOR_TYPE::RED,
                {
                    { 0, COLOR_TYPE::BLUE },
                    { 1, COLOR_TYPE::YELLOW },
                    { 2, COLOR_TYPE::GREEN },
                }
            },
            {
                COLOR_TYPE::BLUE,
                {
                    { 0, COLOR_TYPE::RED },
                    { 1, COLOR_TYPE::GREEN },
                    { 2, COLOR_TYPE::RED },
                }
            },
            {
                COLOR_TYPE::GREEN,
                {
                    { 0, COLOR_TYPE::YELLOW },
                    { 1, COLOR_TYPE::BLUE },
                    { 2, COLOR_TYPE::YELLOW },
                }
            },
            {
                COLOR_TYPE::YELLOW,
                {
                    { 0, COLOR_TYPE::GREEN },
                    { 1, COLOR_TYPE::RED },
                    { 2, COLOR_TYPE::BLUE },
                }
            }
        }
    },
    // Table 2: If the serial number does not contain a vowel
    {
        WITHOUT_VOWEL,
        {
            {
                COLOR_TYPE::RED,
                {
                    { 0, COLOR_TYPE::BLUE },
                    { 1, COLOR_TYPE::RED },
                    { 2, COLOR_TYPE::YELLOW },
                }
            },
            {
                COLOR_TYPE::BLUE,
                {
                    { 0, COLOR_TYPE::YELLOW },
                    { 1, COLOR_TYPE::BLUE },
                    { 2, COLOR_TYPE::GREEN },
                }
            },
            {
                COLOR_TYPE::GREEN,
                {
                    { 0, COLOR_TYPE::GREEN },
                    { 1, COLOR_TYPE::YELLOW },
                    { 2, COLOR_TYPE::BLUE },
                }
            },
            {
                COLOR_TYPE::YELLOW,
                {
                    { 0, COLOR_TYPE::RED },
                    { 1, COLOR_TYPE::GREEN },
                    { 2, COLOR_TYPE::RED },
                }
            }
        }
    },
};
