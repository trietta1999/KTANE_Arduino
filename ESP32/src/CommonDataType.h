/**
 * @brief Common data type
 */

#ifndef _COMMON_DATATYPE_H
#define _COMMON_DATATYPE_H

#include <string>
#include <unordered_map>

#define MINUTE_POS 0
#define SECOND_POS 1

#define TIMECYCLE_0 1000
#define TIMECYCLE_1 500
#define TIMECYCLE_2 300

#define BEEP_FRE 3000
#define BEEP_INCREASE_DURATION 100
#define BEEP_TIMEOUT 5000

#define STATE_CHECKED 3
#define STATE_UNCHECK 2

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

EXTERN_MAP_ENUM_STR(LABEL_INDICATOR)
EXTERN_MAP_ENUM_STR(BATTERY_TYPE)
EXTERN_MAP_ENUM_STR(COMPORT_TYPE)

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
