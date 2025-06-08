/**
 * @brief Common service library
 */

#ifdef _WIN64
#include <iostream>
#include <iomanip>
#include <thread>
#else
#include <esp_random.h>
#endif
#include "CommonService.h"
#include "CommonData.h"
#include "CommonLibrary.h"

int8_t minute = 0, second = 0;
uint64_t currentTime = 0;
bool timerFlag = false;

#ifdef _WIN64
void AttachConsoleWindow()
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
}
#else
#include <BluetoothSerial.h>
BluetoothSerial SerialBT;
#endif

void RunTimer()
{
#ifdef HOST_TIMER
#ifdef _WIN64
    while (!sys_gui::IsStarted.GetValue())
    {
        ::Sleep(10);
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
    minute = std::get<MINUTE_POS>(sys_host::TimeClock.GetValue());
    second = std::get<SECOND_POS>(sys_host::TimeClock.GetValue());

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        while ((minute >= 0) && (sys_gui::SuccessState.GetValue() != STATE_CHECKED) && (sys_host::StrikeNum.GetValue() < STRIKE_NUM_MAX))
        {
            while ((second >= 0) && (sys_gui::SuccessState.GetValue() != STATE_CHECKED) && (sys_host::StrikeNum.GetValue() < STRIKE_NUM_MAX))
            {
                ::Beep(BEEP_FRE, BEEP_INCREASE_DURATION);

                SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
                std::cout << std::setfill('0') << std::setw(2) << std::to_string(minute) << ":"
                    << std::setw(2) << std::to_string(second);

                sys_host::TimeClock.SetValue(std::make_pair(minute, second));

                second--;

                ::Sleep(sys_host::TimeCycle.GetValue());
            }

            minute--;
            second = 59;
        }

        sys_host::TimeOut.SetValue(true);
    }
#else
    if (sys_gui::IsStarted.GetValue())
    {
        if (!timerFlag)
        {
            //minute = std::get<MINUTE_POS>(sys_host::TimeClock.GetValue());
            second = std::get<SECOND_POS>(sys_host::TimeClock.GetValue());
            minute = 1;
            currentTime = millis();
            timerFlag = true;
        }

        if ((sys_gui::SuccessState.GetValue() != STATE_CHECKED) && (sys_host::StrikeNum.GetValue() < STRIKE_NUM_MAX) && !sys_host::TimeOut.GetValue())
        {
            if (millis() - currentTime >= sys_host::TimeCycle.GetValue())
            {
                if (minute >= 0)
                {
                    sys_host::TimeClock.SetValue(std::make_pair(minute, second));

                    second--;

                    if (second < 0)
                    {
                        minute--;
                        second = 59;
                    }
                }
                else
                {
                    sys_host::TimeOut.SetValue(true);
                }

                currentTime = millis();
            }
        }
        else
        {
            sys_host::TimeOut.SetValue(true);
        }
    }
#endif
#endif
}

void InitData()
{
#ifdef HOST_TIMER
#ifdef _WIN64
    uint32_t seed = time(0);
#else
    uint32_t seed = esp_random();

    SerialBT.begin(CLIENT_NAME);
#endif
    srand(seed);

    sys_host::RandomSeed.SetValue(seed);
    sys_host::LabelIndicator.SetValue((LABEL_INDICATOR)RandomRange(0, (uint8_t)LABEL_INDICATOR::MAX));
    sys_host::BatteryType.SetValue((BATTERY_TYPE)RandomRange(0, (uint8_t)BATTERY_TYPE::MAX));
    sys_host::ComPortType.SetValue((COMPORT_TYPE)RandomRange(0, (uint8_t)COMPORT_TYPE::MAX));
    sys_host::BatteryNum.SetValue(RandomRange(1, 5));
    sys_host::SerialNum.SetValue(GenerateSerialNumber());

    sys_host::StrikeNum.SetValue(0);
    sys_host::TimeCycle.SetValue(TIMECYCLE_0);
    sys_host::TimeOut.SetValue(false);
    sys_gui::SuccessState.SetValue(INCORRECT);
    sys_gui::IsStarted.SetValue(false);
#else
    auto jsonDoc = CommonGetRequest(WM_SYSINIT_GET);

    sys_host::RandomSeed.SetValue(jsonDoc[STR(RandomSeed)].as<uint32_t>());
    sys_host::LabelIndicator.SetValue((LABEL_INDICATOR)jsonDoc[STR(LabelIndicator)].as<uint8_t>());
    sys_host::BatteryType.SetValue((BATTERY_TYPE)jsonDoc[STR(BatteryType)].as<uint8_t>());
    sys_host::ComPortType.SetValue((COMPORT_TYPE)jsonDoc[STR(ComPortType)].as<uint8_t>());
    sys_host::BatteryNum.SetValue(jsonDoc[STR(BatteryNum)].as<uint8_t>());
    sys_host::SerialNum.SetValue(jsonDoc[STR(SerialNum)].as<const char*>());
    sys_host::StrikeNum.SetValue(jsonDoc[STR(StrikeNum)].as<uint8_t>());
    sys_gui::IsStarted.SetValue(jsonDoc[STR(IsStarted)].as<bool>());
    sys_gui::SuccessState.SetValue(INCORRECT);

    srand(sys_host::RandomSeed.GetValue());
#endif

#ifdef _WIN64
    AttachConsoleWindow();
#endif

#ifdef _WIN64
    debug_println("===== Dummy Data Initialized =====");
    debug_println("RandomSeed: " + std::to_string(sys_host::RandomSeed.GetValue()));
    debug_println("LabelIndicator: " + map_LABEL_INDICATOR[sys_host::LabelIndicator.GetValue()]);
    debug_println("BatteryType: " + map_BATTERY_TYPE[sys_host::BatteryType.GetValue()]);
    debug_println("ComPortType: " + map_COMPORT_TYPE[sys_host::ComPortType.GetValue()]);
    debug_println("BatteryNum: " + std::to_string(sys_host::BatteryNum.GetValue()));
    debug_println("SerialNum: " + sys_host::SerialNum.GetValue());
    debug_println("==================================");

#ifdef HOST_TIMER
    std::thread([]() {
        RunTimer();
        }).detach();
#endif
#endif
}

void ProcessData()
{
#ifndef _WIN64
    if (SerialBT.available()) {
        String read = SerialBT.readStringUntil('\n');

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
            auto orderIndex = OrderIndex.GetValue();
            debug_println("ColumnIndex: " + std::to_string(ColumnIndex.GetValue()));
            debug_println("OrderIndex:");

            for (uint8_t i = 0; i < orderIndex.size(); i++)
            {
                debug_println(std::to_string(orderIndex[i]));
            }
        }
    }
#endif

#ifdef HOST_TIMER
    if (sys_host::StrikeState.GetState())
    {
        sys_host::StrikeNum.SetValue(sys_host::StrikeNum.GetValue() + 1);

        switch (sys_host::StrikeNum.GetValue())
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
        case 3:
            sys_host::TimeCycle.SetValue(TIMECYCLE_3);
            break;
        default:
            break;
        }

        sys_host::StrikeState.SetValue(false);

#ifdef _WIN64
        ::MessageBox(NULL, L"", L"", MB_ICONERROR);
#endif
    }

    if (sys_host::TimeOut.GetState()
#ifdef _WIN64
        || (sys_host::StrikeNum.GetValue() >= STRIKE_NUM_MAX)
#endif
        )
    {
        if (sys_gui::SuccessState.GetValue() == INCORRECT)
        {
            sys_gui::SuccessState.SetValue(STATE_UNCHECK);
#ifdef _WIN64
            ::Beep(BEEP_FRE, BEEP_TIMEOUT);
            sys_host::StrikeNum.SetValue(STRIKE_NUM_MAX - 1);
#endif
        }
        else
        {
#ifdef _WIN64
            ::MessageBox(NULL, L"", L"", MB_ICONINFORMATION);
#endif
        }

        sys_host::TimeOut.SetValue(false);
        sys_gui::IsStarted.SetValue(false);
    }
#endif

#ifndef HOST_TIMER
    // Client process
#endif
}

void ProcessRequest(HWND hwnd, uint32_t msg, JsonDocument jsonDocIn)
{
#ifdef HOST_TIMER
#ifdef _WIN64
    JsonDocument jsonDoc;

    switch (msg)
    {
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

    case WM_SYSINIT_GET:
    {
        jsonDoc[STR(RandomSeed)] = sys_host::RandomSeed.GetValue();
        jsonDoc[STR(LabelIndicator)] = (uint8_t)sys_host::LabelIndicator.GetValue();
        jsonDoc[STR(BatteryType)] = (uint8_t)sys_host::BatteryType.GetValue();
        jsonDoc[STR(ComPortType)] = (uint8_t)sys_host::ComPortType.GetValue();
        jsonDoc[STR(BatteryNum)] = sys_host::BatteryNum.GetValue();
        jsonDoc[STR(SerialNum)] = sys_host::SerialNum.GetValue();
        jsonDoc[STR(StrikeNum)] = sys_host::StrikeNum.GetValue();
        jsonDoc[STR(IsStarted)] = sys_gui::IsStarted.GetValue();
    }
    break;

    case WM_STOP_ALL:
    {
        jsonDoc["stop"] = true;
    }
    break;

    case WM_START:
    {
        auto mapModuleStatus = sys_gui::ModuleStatusMap.GetValue();

        if (mapModuleStatus[jsonDocIn["module"].as<const char*>()] == MODULE_STATUS::ENABLE)
        {
            jsonDocIn["status"] = (uint8_t)MODULE_STATUS::ENABLE;
        }
        else
        {
            jsonDocIn["status"] = (uint8_t)MODULE_STATUS::DISABLE;
        }

        jsonDoc = jsonDocIn;
    }
    break;

    case WM_READY:
    {
        jsonDoc["ready"] = true;
    }
    break;

    default:
        break;
    }

    char jsonDocStr[MAX_SIZE] = { 0 };

    serializeJson(jsonDoc, jsonDocStr);

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
    // Arduino process
#endif
#else
    // Client process
#endif
}

JsonDocument CommonGetRequest(uint32_t msg)
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

    return sys_host::JsonResponse.GetValue();
#else
    // Arduino process
    JsonDocument jsonDoc;
    return jsonDoc;
#endif
}

JsonDocument CommonGetRequestWithData(uint32_t msg, JsonDocument jsonValue)
{
#ifdef _WIN64
    JsonDocument jsonDoc;
    char jsonDocStr[MAX_SIZE] = { 0 };

    jsonValue["client_name"] = CLIENT_NAME_FOR_JSON;

    serializeJson(jsonValue, jsonDocStr);

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

    ::SendMessage(hwnd, WM_SET_CLIENT_HANDLE, msg, NULL);
    ::SendMessage(hwnd, WM_REQUEST_WITH_DATA, msg, NULL);

    return sys_host::JsonResponse.GetValue();
#else
    // Arduino process
    JsonDocument jsonDoc;
    return jsonDoc;
#endif
}
