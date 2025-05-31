/**
 * @brief Common data type
 */

#ifndef _COMMON_DATATYPE_H
#define _COMMON_DATATYPE_H

#ifdef ARDUINO // Temporary Service for Arduino
#define HOST_TIMER
#endif

#include <cstdint>
#include <string>
#include <unordered_map>

#define STR(a) #a

#ifdef _WIN64
#define HOST_NAME mapWstr_MODULE_NAME[MODULE_NAME::HostTimer].c_str()
#define CLIENT_NAME mapWstr_MODULE_NAME[MODULE_NAME::Wires].c_str()
#define CLIENT_NAME_FOR_JSON map_MODULE_NAME[MODULE_NAME::Wires].c_str()
#else
#define HOST_NAME map_MODULE_NAME[MODULE_NAME::HostTimer].c_str()
#define CLIENT_NAME map_MODULE_NAME[MODULE_NAME::Wires].c_str()
#endif

#ifdef _WIN64
#include <Windows.h>
#define debug_println(a) std::cout << std::string(a) << "\n"
#define SHARED_MEM L"SharedMemoryJson"
#define MAX_SIZE 1000
#define BUFFER_SIZE sizeof(char) * MAX_SIZE
#else
#define WM_USER 0x0400
#define HWND void*
#define debug_println(a) SerialBT.println(std::string(a).c_str())
#endif

enum
{
    WM_USER_MIN = WM_USER,
    WM_SET_CLIENT_HANDLE,
    WM_REQUEST,
    WM_REQUEST_WITH_DATA,
    WM_RESPONSE,
    WM_READY,
    WM_TIMER_GET,
    WM_STRIKENUM_GET,
    WM_STRIKESTATE_SET,
    WM_SYSINIT_GET,
    WM_STOP_ALL,
    WM_START,
};

#define STRIKE_NUM_MAX 4

#define INCORRECT (uint8_t)(-1)

#define MINUTE_POS 0
#define SECOND_POS 1

#define TIMECYCLE_0 1000
#define TIMECYCLE_1 800
#define TIMECYCLE_2 600
#define TIMECYCLE_3 400

#define BEEP_FRE 3000
#define BEEP_INCREASE_DURATION 50
#define BEEP_TIMEOUT 2000

#define STATE_CHECKED 3
#define STATE_UNCHECK 2

#define TO_ENUM(enum_name, item) item,
#define TO_STRING(enum_name, item) { enum_name::item, #item },

#define MAP_ENUM_STR(enum_name, enum_def) std::unordered_map<enum_name, std::string> map_##enum_name = { enum_def(enum_name,TO_STRING) };
#define EXTERN_MAP_ENUM_STR(enum_name) extern std::unordered_map<enum_name, std::string> map_##enum_name;

#ifdef _WIN64
#define TO_WSTRING(enum_name, item) { enum_name::item, L#item },
#define MAP_ENUM_WSTR(enum_name, enum_def) std::unordered_map<enum_name, std::wstring> mapWstr_##enum_name = { enum_def(enum_name,TO_WSTRING) };
#define EXTERN_MAP_ENUM_WSTR(enum_name) extern std::unordered_map<enum_name, std::wstring> mapWstr_##enum_name;
#endif

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

#define DEF_MODULE_NAME(e, CREATE) \
        CREATE(e, HostTimer) \
        CREATE(e, Wires) \
        CREATE(e, TheButton) \
        CREATE(e, Keypads) \
        CREATE(e, SimonSays) \
        CREATE(e, WhosOnFirst) \
        CREATE(e, Memory) \
        CREATE(e, MorseCode) \
        CREATE(e, ComplicatedWires) \
        CREATE(e, WireSequences) \
        CREATE(e, Mazes) \
        CREATE(e, Passwords) \
        CREATE(e, VentingGas) \
        CREATE(e, CapacitorDischarge) \
        CREATE(e, Knobs) \

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

enum class MODULE_NAME
{
    DEF_MODULE_NAME(MODULE_NAME, TO_ENUM)
    MAX
};

enum class MODULE_STATUS
{
    ENABLE = 1,
    DISABLE,
};

EXTERN_MAP_ENUM_STR(LABEL_INDICATOR)
EXTERN_MAP_ENUM_STR(BATTERY_TYPE)
EXTERN_MAP_ENUM_STR(COMPORT_TYPE)
EXTERN_MAP_ENUM_STR(MODULE_NAME)

#ifdef _WIN64
EXTERN_MAP_ENUM_WSTR(MODULE_NAME)
#endif

#pragma endregion

// Allow modification
#pragma region Custom_datatype
#define COLOR uint32_t
#define NON_COLOR 0x000001

#define DEF_WIRECOLOR_TYPE(e, CREATE) \
        CREATE(e, RED) \
        CREATE(e, WHITE) \
        CREATE(e, BLUE) \
        CREATE(e, YELLOW) \
        CREATE(e, BLACK) \
        CREATE(e, PINK) \

enum class WIRECOLOR_TYPE
{
    MIN,
    DEF_WIRECOLOR_TYPE(WIRECOLOR_TYPE, TO_ENUM)
    MAX
};
EXTERN_MAP_ENUM_STR(WIRECOLOR_TYPE)

extern std::unordered_map<WIRECOLOR_TYPE, COLOR> mapColor;

#pragma endregion

#endif // !_COMMON_DATATYPE_H
