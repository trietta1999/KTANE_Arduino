/**
 * @brief Common data type
 */

#ifndef _COMMON_DATATYPE_H
#define _COMMON_DATATYPE_H

#include <cstdint>
#include <tuple>
#include <vector>
#include <array>
#include <string>
#include <unordered_map>

#define STR(a) #a

#ifdef _WIN64
#define HOST_NAME mapWstr_MODULE_NAME[MODULE_NAME::HostTimer].c_str()
#define CLIENT_NAME mapWstr_MODULE_NAME[MODULE_NAME::SimonSays].c_str()
#define CLIENT_NAME_FOR_JSON map_MODULE_NAME[MODULE_NAME::SimonSays].c_str()
#else
#define HOST_NAME map_MODULE_NAME[MODULE_NAME::HostTimer].c_str()
#define CLIENT_NAME map_MODULE_NAME[MODULE_NAME::SimonSays].c_str()
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
#define HWND uint8_t

#define debug_println(a) Serial.println(std::string(a).c_str())
#define MILLISEC_GET millis()

#define INPUT_PIN 22
#define BUZZER_PIN 26

#define WIFI_SSID "KTANE_Arduino"
#define WIFI_PASS "KTANE_Arduino"

#define IP_ADD_1 192
#define IP_ADD_2 168
#define IP_ADD_3 0
#define IP_ADD_4 (uint8_t)MODULE_NAME::SimonSays

#define NETMASK_1 255
#define NETMASK_2 255
#define NETMASK_3 255
#define NETMASK_4 0

#define HTTP_OK 200
#define HTTP_NOT_FOUND 404
#define HTTP_RESPONSE "OK"

struct data_pack_t {
    uint32_t base_msg;
    uint32_t msg;
    char data[MAX_SIZE];
};
#endif

enum
{
    WM_USER_MIN = WM_USER,
    WM_SET_CLIENT_HANDLE, // Save client handle
    WM_REQUEST,           // Request/get from other message
    WM_REQUEST_WITH_DATA, // Request/get from other message with data
    WM_RESPONSE,          // Response message from host to client
    WM_CLIENT_RESPONSE,   // Response message from client to host
    WM_SET_CLIENTSTATE,   // Notify to set ON/OFF status to selected clients
    WM_TIMER_GET,         // Client get timer from host
    WM_STRIKENUM_GET,     // Client get strike count from host
    WM_STRIKESTATE_SET,   // Client notify host to set strike status
    WM_SUCCESSSTATE_SET,  // Client notify host to set client success status
    WM_SYSINIT_GET,       // Client get init system data from host
    WM_STOP_ALL,          // Notify for stoping all client
    WM_STOP_COMPLETE,     // Notify for all client stopped to Host
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
        CREATE(e, SystemInfo) \
        CREATE(e, Transporter) \

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
#define WITH_VOWEL STR(WITH_VOWEL)
#define WITHOUT_VOWEL STR(WITHOUT_VOWEL)
#define BLINK_PERIOD 500
#define BLINK_REST 5000

#define DEF_COLOR_TYPE(e, CREATE) \
        CREATE(e, BLUE) \
        CREATE(e, YELLOW) \
        CREATE(e, GREEN) \
        CREATE(e, RED) \

enum class COLOR_TYPE
{
    MIN,
    DEF_COLOR_TYPE(COLOR_TYPE, TO_ENUM)
    MAX
};

EXTERN_MAP_ENUM_STR(COLOR_TYPE)

extern std::unordered_map<const char*, std::unordered_map<COLOR_TYPE, std::unordered_map<uint8_t, COLOR_TYPE>>> mapColorSequence;
#pragma endregion

#endif // !_COMMON_DATATYPE_H
