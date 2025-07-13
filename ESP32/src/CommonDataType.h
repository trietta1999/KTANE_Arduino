/**
 * @brief Common data type
 */

#ifndef _COMMON_DATATYPE_H
#define _COMMON_DATATYPE_H

#ifdef ARDUINO // Temporary Service for Arduino
#define HOST_TIMER
#endif

#include <cstdint>
#include <tuple>
#include <array>
#include <vector>
#include <string>
#include <unordered_map>

#define STR(a) #a

#ifdef _WIN64
#define HOST_NAME mapWstr_MODULE_NAME[MODULE_NAME::HostTimer].c_str()
#define CLIENT_NAME mapWstr_MODULE_NAME[MODULE_NAME::Memory].c_str()
#define CLIENT_NAME_FOR_JSON map_MODULE_NAME[MODULE_NAME::Memory].c_str()
#else
#define HOST_NAME map_MODULE_NAME[MODULE_NAME::HostTimer].c_str()
#define CLIENT_NAME map_MODULE_NAME[MODULE_NAME::Memory].c_str()
#endif

#define MAX_SIZE 1000
#define BUFFER_SIZE sizeof(char) * MAX_SIZE

#ifdef _WIN64
#include <Windows.h>
#define MILLISEC_GET ::GetTickCount64()
#define debug_println(a) std::cout << std::string(a) << "\n"
#define SHARED_MEM L"SharedMemoryJson"
#else
#include <Arduino.h>
#define WM_USER 0x0400
#define HWND void*
#define DATA_HEADER String("REQUEST|")
#define DATA_TRAILER String("|ENDREQUEST")
#define debug_println(a) SerialBT.println(std::string(a).c_str())
#define MILLISEC_GET millis()
#endif

enum
{
    WM_USER_MIN = WM_USER,
    WM_SET_CLIENT_HANDLE, // Save client handle
    WM_REQUEST,           // Request/get from other message
    WM_REQUEST_WITH_DATA, // Request/get from other message with data
    WM_RESPONSE,          // Response message from host to client
    WM_SET_CLIENTSTATE,   // Notify to set ON/OFF status to specific client
    WM_START_ALL,         // Notify for starting all client
    WM_TIMER_GET,         // Client get timer from host
    WM_STRIKENUM_GET,     // Client get strike count from host
    WM_STRIKESTATE_SET,   // Client notify host to set strike status
    WM_SUCCESSSTATE_SET,  // Client notify host to set client success status
    WM_SYSINIT_GET,       // Client get init system data from host
    WM_STOP_ALL,          // Notify for stoping all client
};

#define STRIKE_NUM_MAX 3

#define INCORRECT (uint8_t)(-1)

#define MINUTE_POS 0
#define SECOND_POS 1
#define MILLIS_POS 2

#define TIMECYCLE_0 1000
#define TIMECYCLE_1 600
#define TIMECYCLE_2 400

#define BEEP_FRE 3000
#define BEEP_INCREASE_DURATION 50
#define BEEP_TIMEOUT 2000

#define STATE_CHECKED 3
#define STATE_UNCHECK 2

#define COLOR uint32_t
#define NON_COLOR 0x000001

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
    OFF,
    ON,
    START,
    SUCCESS,
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
#define STAGE_NUM 5
#define BUTTON_NUM 4
#define POSITION_POS 0
#define VALUE_POS 1

#define DEF_POSTION_TYPE(e, CREATE) \
        CREATE(e, FIRST) \
        CREATE(e, SECOND) \
        CREATE(e, THIRD) \
        CREATE(e, FOURTH) \

enum class POSTION_TYPE
{
    DEF_POSTION_TYPE(POSTION_TYPE, TO_ENUM)
    INVALID
};

EXTERN_MAP_ENUM_STR(POSTION_TYPE)

#pragma endregion

#endif // !_COMMON_DATATYPE_H
