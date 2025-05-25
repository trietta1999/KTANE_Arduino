/**
 * @brief Common data type
 */

#ifndef _COMMON_DATATYPE_H
#define _COMMON_DATATYPE_H

#include <cstdint>
#include <string>
#include <unordered_map>

#define INCORRECT (uint8_t)(-1)

#define MINUTE_POS 0
#define SECOND_POS 1

#define FIRST_EVENT 0
#define SECOND_EVENT 1
#define SPECIAL_NUM 2S

#define TIMECYCLE_0 1000
#define TIMECYCLE_1 800
#define TIMECYCLE_2 600
#define TIMECYCLE_3 400

#define BEEP_FRE 3000
#define BEEP_INCREASE_DURATION 100
#define BEEP_TIMEOUT 5000

#define STATE_CHECKED 3
#define STATE_UNCHECK 2

#define COLOR uint32_t
#define NON_COLOR 0x000001
#define COLOR_RED 0xFF0000
#define COLOR_GREEN 0x35C61F
#define COLOR_WHITE 0xFFFFFF

#define VERIFY_CODE "241"

#define TO_ENUM(enum_name, item) item,
#define TO_STRING(enum_name, item) { enum_name::item, #item },

#define MAP_ENUM_STR(enum_name, enum_def) std::unordered_map<enum_name, std::string> map_##enum_name = { enum_def(enum_name,TO_STRING) };
#define EXTERN_MAP_ENUM_STR(enum_name) extern std::unordered_map<enum_name, std::string> map_##enum_name;

 // Do not modify
#pragma region System_datatype
#define DEF_LABEL_INDICATOR(e, CREATE) \
        CREATE(e, SND) \
        CREATE(e, CLR) \
        CREATE(e, CAR) \
        CREATE(e, IND) \
        CREATE(e, FRQ) \
        CREATE(e, SIG) \
        CREATE(e, NSA) \
        CREATE(e, MSA) \
        CREATE(e, TRN) \
        CREATE(e, BOB) \
        CREATE(e, FRK) \

#define DEF_BATTERY_TYPE(e, CREATE) \
        CREATE(e, AA) \
        CREATE(e, D) \

#define DEF_COMPORT_TYPE(e, CREATE) \
        CREATE(e, DVID) \
        CREATE(e, Parallel) \
        CREATE(e, PS2) \
        CREATE(e, RJ45) \
        CREATE(e, Serial) \
        CREATE(e, Stereo_RCA) \

#define DEF_COLOR_TYPE(e, CREATE) \
        CREATE(e, RED) \
        CREATE(e, WHITE) \
        CREATE(e, BLUE) \
        CREATE(e, YELLOW) \
        CREATE(e, PINK) \
        CREATE(e, BLACK) \

#define DEF_BTN_LABEL_TYPE(e, CREATE) \
        CREATE(e, Abort) \
        CREATE(e, Detonate) \
        CREATE(e, Hold) \
        CREATE(e, Press) \

enum class LABEL_INDICATOR
{
    DEF_LABEL_INDICATOR(LABEL_INDICATOR, TO_ENUM)
    MAX
};

enum class BATTERY_TYPE
{
    DEF_BATTERY_TYPE(BATTERY_TYPE, TO_ENUM)
    MAX
};

enum class COMPORT_TYPE
{
    DEF_COMPORT_TYPE(COMPORT_TYPE, TO_ENUM)
    MAX
};

enum class COLOR_TYPE
{
    MIN,
    DEF_COLOR_TYPE(COLOR_TYPE, TO_ENUM)
    MAX
};

enum class BTN_LABEL_TYPE
{
    MIN,
    DEF_BTN_LABEL_TYPE(BTN_LABEL_TYPE, TO_ENUM)
    MAX
};

EXTERN_MAP_ENUM_STR(LABEL_INDICATOR)
EXTERN_MAP_ENUM_STR(BATTERY_TYPE)
EXTERN_MAP_ENUM_STR(COMPORT_TYPE)
EXTERN_MAP_ENUM_STR(COLOR_TYPE)
EXTERN_MAP_ENUM_STR(BTN_LABEL_TYPE)

#pragma endregion

// Allow modification
#pragma region Custom_datatype

#pragma endregion

#endif // !_COMMON_DATATYPE_H
