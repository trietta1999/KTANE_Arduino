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

MAP_ENUM_STR(TEXT_TYPE, DEF_TEXT_TYPE)

std::unordered_map<char, std::string> mapLetterMorsePattern = {
    { 'A', ".-" },
    { 'B', "-..." },
    { 'C', "-.-." },
    { 'D', "-.." },
    { 'E', "." },
    { 'F', "..-." },
    { 'G', "--." },
    { 'H', "...." },
    { 'I', ".." },
    { 'J', ".---" },
    { 'K', "-.-" },
    { 'L', ".-.." },
    { 'M', "--" },
    { 'N', "-." },
    { 'O', "---" },
    { 'P', ".--." },
    { 'Q', "--.-" },
    { 'R', ".-." },
    { 'S', "..." },
    { 'T', "-" },
    { 'U', "..-" },
    { 'V', "...-" },
    { 'W', ".--" },
    { 'X', "-..-" },
    { 'Y', "-.--" },
    { 'Z', "--.." },
};

std::unordered_map<TEXT_TYPE, uint16_t> mapTextFrequency = {
    { TEXT_TYPE::SHELL , 3505 },
    { TEXT_TYPE::HALLS , 3515 },
    { TEXT_TYPE::SLICK , 3522 },
    { TEXT_TYPE::TRICK , 3532 },
    { TEXT_TYPE::BOXES , 3535 },
    { TEXT_TYPE::LEAKS , 3542 },
    { TEXT_TYPE::STROBE, 3545 },
    { TEXT_TYPE::BISTRO, 3552 },
    { TEXT_TYPE::FLICK , 3555 },
    { TEXT_TYPE::BOMBS , 3565 },
    { TEXT_TYPE::BREAK , 3572 },
    { TEXT_TYPE::BRICK , 3575 },
    { TEXT_TYPE::STEAK , 3582 },
    { TEXT_TYPE::STING , 3592 },
    { TEXT_TYPE::VECTOR, 3595 },
    { TEXT_TYPE::BEATS , 3600 },
};
