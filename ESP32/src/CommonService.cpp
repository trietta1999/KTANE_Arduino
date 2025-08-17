/**
 * @brief Common service library
 */

#include "CommonService.h"
#include "CommonData.h"
#include "CommonLibrary.h"
#ifdef _WIN64
#include <iostream>
#include <iomanip>
#else
#include <esp_random.h>
#include "../Hardware.h"
#endif

#ifdef _WIN64
void AttachConsoleWindow()
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
}
#endif

void InitData()
{
#ifndef _WIN64
    HardwareSetup();
#endif

#ifdef HOST_TIMER
#ifndef _WIN64
    uint32_t seed = esp_random();
#else
    uint32_t seed = time(0);
#endif

    // Set random seed
    srand(seed);

    // Create random init data
    sys_host::RandomSeed.SetValue(seed);
    sys_host::LabelIndicator.SetValue((LABEL_INDICATOR)RandomRange(0, (uint8_t)LABEL_INDICATOR::MAX));
    sys_host::BatteryType.SetValue((BATTERY_TYPE)RandomRange(0, (uint8_t)BATTERY_TYPE::MAX));
    sys_host::ComPortType.SetValue((COMPORT_TYPE)RandomRange(0, (uint8_t)COMPORT_TYPE::MAX));
    sys_host::BatteryNum.SetValue(RandomRange(1, 5));
    sys_host::SerialNum.SetValue(GenerateSerialNumber());
    sys_host::EndlessTimeClock.SetValue(std::make_tuple(0, 0, 0));

    sys_host::StrikeNum.SetValue(0);
    sys_host::TimeCycle.SetValue(TIMECYCLE_0);
    sys_gui::SuccessState.SetValue(INCORRECT);
#else
    // Get init data from HostTimer
    auto jsonDoc = CommonSendRequest(WM_SYSINIT_GET);

    // Set init data
    sys_host::RandomSeed.SetValue(jsonDoc[STR(RandomSeed)].as<uint32_t>());
    sys_host::LabelIndicator.SetValue((LABEL_INDICATOR)jsonDoc[STR(LabelIndicator)].as<uint8_t>());
    sys_host::BatteryType.SetValue((BATTERY_TYPE)jsonDoc[STR(BatteryType)].as<uint8_t>());
    sys_host::ComPortType.SetValue((COMPORT_TYPE)jsonDoc[STR(ComPortType)].as<uint8_t>());
    sys_host::BatteryNum.SetValue(jsonDoc[STR(BatteryNum)].as<uint8_t>());
    sys_host::SerialNum.SetValue(jsonDoc[STR(SerialNum)].as<const char*>());
    sys_host::StrikeNum.SetValue(jsonDoc[STR(StrikeNum)].as<uint8_t>());
    sys_gui::SuccessState.SetValue(INCORRECT);

    // Set random seed
    srand(sys_host::RandomSeed.GetValue());
#endif

#ifdef _WIN64
    AttachConsoleWindow();
#endif

    // Print init data
#ifdef _WIN64
    debug_println("===== Dummy Data Initialized =====");
    debug_println("RandomSeed: " + std::to_string(sys_host::RandomSeed.GetValue()));
    debug_println("LabelIndicator: " + map_LABEL_INDICATOR[sys_host::LabelIndicator.GetValue()]);
    debug_println("BatteryType: " + map_BATTERY_TYPE[sys_host::BatteryType.GetValue()]);
    debug_println("ComPortType: " + map_COMPORT_TYPE[sys_host::ComPortType.GetValue()]);
    debug_println("BatteryNum: " + std::to_string(sys_host::BatteryNum.GetValue()));
    debug_println("SerialNum: " + sys_host::SerialNum.GetValue());
    debug_println("==================================");
#endif
}

void ProcessData()
{
#ifndef _WIN64
    // Read data from serial bluetooth
    if (Serial.available()) {
        String read = Serial.readStringUntil('\n');

        // Print init data
        if (read == "sys_data") {
            debug_println("===== Dummy Data Initialized =====");
            debug_println("RandomSeed: " + std::to_string(sys_host::RandomSeed.GetValue()));
            debug_println("LabelIndicator: " + map_LABEL_INDICATOR[sys_host::LabelIndicator.GetValue()]);
            debug_println("BatteryType: " + map_BATTERY_TYPE[sys_host::BatteryType.GetValue()]);
            debug_println("ComPortType: " + map_COMPORT_TYPE[sys_host::ComPortType.GetValue()]);
            debug_println("BatteryNum: " + std::to_string(sys_host::BatteryNum.GetValue()));
            debug_println("SerialNum: " + sys_host::SerialNum.GetValue());
            debug_println("==================================");
        }
        else if (read == "gui_correct")
        {
            debug_println("\"Y\" is answered to \"VENT GAS?\" There is a two second delay");
            debug_println("\"N\" is answered to \"DETONATE?\" There is a two second delay.");
            debug_println("Answering \"N\" to \"VENT GAS?\" will only pop up a message \"VENTING PREVENTS EXPLOSIONS\" but does not cause a strike nor reset the timer.");
        }
    }

    // Re-connect WiFi if disconnected
    WiFiReconnect();
#endif

#ifdef HOST_TIMER
    // Update strike num
    if (sys_host::StrikeState.GetValue())
    {
        auto strikeNum = sys_host::StrikeNum.GetValue() + 1;

        // Update time cycle
        switch (strikeNum)
        {
        case 0:
            sys_host::TimeCycle.SetValue(TIMECYCLE_0);
            break;
        case 1:
            sys_host::TimeCycle.SetValue(TIMECYCLE_1);
            break;
        case 2:
            sys_host::TimeCycle.SetValue(TIMECYCLE_2);
            break;
        default:
            break;
        }

        // Update strike num
        sys_host::StrikeNum.SetValue(strikeNum);

        // Reset strike state flag
        sys_host::StrikeState.SetValue(false);

#ifdef _WIN64
        ::MessageBox(NULL, L"", L"", MB_ICONERROR);
#endif
    }
#else
    // Client process
#endif
}

void ProcessRequest(HWND hwnd, uint32_t msg, JsonDocument jsonDocIn)
{
#ifdef HOST_TIMER
    JsonDocument jsonDoc;

    switch (msg)
    {
    case WM_START_ALL:
    {
        jsonDoc["start"] = (uint8_t)MODULE_STATUS::START;
    }
    break;

    case WM_TIMER_GET:
    {
        auto time = sys_host::TimeClock.GetValue();

        jsonDoc["minute"] = std::get<MINUTE_POS>(time);
        jsonDoc["second"] = std::get<SECOND_POS>(time);
    }
    break;

    case WM_STRIKENUM_GET:
    {
        jsonDoc[STR(StrikeNum)] = sys_host::StrikeNum.GetValue();
    }
    break;

    case WM_STRIKESTATE_SET:
    {
        sys_host::StrikeState.SetValue(true);
    }
    break;

    case WM_SUCCESSSTATE_SET:
    {
        auto mapModuleStatus = sys_gui::ModuleStatusMap.GetValue();

        if (mapModuleStatus[jsonDocIn["module"].as<const char*>()] == MODULE_STATUS::ON)
        {
            mapModuleStatus[jsonDocIn["module"].as<const char*>()] = MODULE_STATUS::SUCCESS;

            sys_gui::ModuleStatusMap.SetValue(mapModuleStatus);
        }
    }
    break;

    case WM_SYSINIT_GET:
    {
        jsonDoc[STR(RandomSeed)] = sys_host::RandomSeed.GetValue();
        jsonDoc[STR(LabelIndicator)] = (uint8_t)sys_host::LabelIndicator.GetValue();
        jsonDoc[STR(BatteryType)] = (uint8_t)sys_host::BatteryType.GetValue();
        jsonDoc[STR(ComPortType)] = (uint8_t)sys_host::ComPortType.GetValue();
        jsonDoc[STR(BatteryNum)] = sys_host::BatteryNum.GetValue();
        jsonDoc[STR(SerialNum)] = sys_host::SerialNum.GetValue();
        jsonDoc[STR(StrikeNum)] = sys_host::StrikeNum.GetValue();
    }
    break;

    case WM_STOP_ALL:
    {
        jsonDoc["stop"] = true;
    }
    break;

    default:
        break;
    }

    char jsonDocStr[MAX_SIZE] = { 0 };
    serializeJson(jsonDoc, jsonDocStr);

#ifdef _WIN64
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUFFER_SIZE, SHARED_MEM);
    if (!hMapFile)
    {
        return;
    }

    LPVOID pBuffer = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
    if (!pBuffer)
    {
        CloseHandle(hMapFile);
        return;
    }

    strcpy((char*)pBuffer, jsonDocStr);

    UnmapViewOfFile(pBuffer);

    ::SendMessage(hwnd, WM_RESPONSE, NULL, NULL);
#else
    data_pack_t byteData = { 0 };
    byteData.target = hwnd;
    byteData.base_msg = WM_RESPONSE;
    byteData.msg = 0;
    strcpy(byteData.data, jsonDocStr);

    SendMessage(byteData);
#endif
#else
    // Client process
#endif
}

JsonDocument CommonSendRequest(uint32_t msg)
{
#ifdef _WIN64
    JsonDocument jsonDoc;

    jsonDoc["client_name"] = CLIENT_NAME_FOR_JSON;
    char jsonDocStr[MAX_SIZE] = { 0 };

    serializeJson(jsonDoc, jsonDocStr);

    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUFFER_SIZE, SHARED_MEM);
    if (!hMapFile)
    {
        return jsonDoc;
    }

    LPVOID pBuffer = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
    if (!pBuffer)
    {
        CloseHandle(hMapFile);
        return jsonDoc;
    }

    strcpy((char*)pBuffer, jsonDocStr);

    UnmapViewOfFile(pBuffer);

    HWND hwnd = ::FindWindow(NULL, HOST_NAME);

    ::SendMessage(hwnd, WM_SET_CLIENT_HANDLE, NULL, NULL);
    ::SendMessage(hwnd, WM_REQUEST, msg, NULL);
#else
    data_pack_t byteData = { 0 };
    byteData.target = (uint8_t)MODULE_NAME::HostTimer;
    byteData.base_msg = WM_REQUEST;
    byteData.msg = msg;

    SendMessage(byteData);
#endif

    return sys_host::JsonResponse.GetValue();
}

JsonDocument CommonSendRequestWithData(uint32_t msg, JsonDocument jsonValue)
{
#ifdef _WIN64
    char jsonDocStr[MAX_SIZE] = { 0 };
    jsonValue["client_name"] = CLIENT_NAME_FOR_JSON;

    serializeJson(jsonValue, jsonDocStr);

    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUFFER_SIZE, SHARED_MEM);
    if (!hMapFile)
    {
        return JsonDocument();
    }

    LPVOID pBuffer = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
    if (!pBuffer)
    {
        CloseHandle(hMapFile);
        return JsonDocument();
    }

    strcpy((char*)pBuffer, jsonDocStr);

    UnmapViewOfFile(pBuffer);

    HWND hwnd = ::FindWindow(NULL, HOST_NAME);

    ::SendMessage(hwnd, WM_SET_CLIENT_HANDLE, msg, NULL);
    ::SendMessage(hwnd, WM_REQUEST_WITH_DATA, msg, NULL);
#else
    char jsonDocStr[MAX_SIZE] = { 0 };
    serializeJson(jsonValue, jsonDocStr);

    data_pack_t byteData = { 0 };
    byteData.target = (uint8_t)MODULE_NAME::HostTimer;
    byteData.base_msg = WM_REQUEST_WITH_DATA;
    byteData.msg = msg;
    strcpy(byteData.data, jsonDocStr);

    SendMessage(byteData);
#endif

    return sys_host::JsonResponse.GetValue();
}
