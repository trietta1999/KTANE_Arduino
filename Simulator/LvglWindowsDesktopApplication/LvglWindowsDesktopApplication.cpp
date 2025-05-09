#include <Windows.h>
#include <thread>
#include <iostream>
#include <iomanip>
#include <LvglWindowsIconResource.h>

#include "lvgl/lvgl.h"
#include "ui/ui.h"
#include "CommonData.h"
#include "CommonLibrary.h"

void AttachConsoleWindow()
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);
}

void RunFakeTimer(int8_t minute)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
    int8_t second = 0;

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        while ((minute >= 0) && (!sys_gui::IsSuccess.GetValue()) && (sys_gui::StrikeNum.GetValue() < 3))
        {
            while ((second >= 0) && (!sys_gui::IsSuccess.GetValue()) && (sys_gui::StrikeNum.GetValue() < 3))
            {
                ::Beep(BEEP_FRE, BEEP_INCREASE_DURATION);

                SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
                std::cout << std::setfill('0') << std::setw(2) << std::to_string(minute) << ":"
                    << std::setw(2) << std::to_string(second);

                sys_gui::TimeClock.SetValue(std::make_pair(minute, second));

                second--;

                ::Sleep(sys_gui::TimeCycle.GetValue());
            }

            minute--;
            second = 59;
        }

        if (!sys_gui::IsSuccess.GetValue())
        {
            ::Beep(BEEP_FRE, BEEP_TIMEOUT);
        }
    }
}

void InitCDataFromFakeTimer()
{
    uint8_t seed = time(0);
    srand(seed);

    sys_host::RandomSeed.SetValue(seed);
    sys_host::LabelIndicator.SetValue((LABEL_INDICATOR)RandomRange(0, (uint8_t)LABEL_INDICATOR::MAX));
    sys_host::BatteryType.SetValue((BATTERY_TYPE)RandomRange(0, (uint8_t)BATTERY_TYPE::MAX));
    sys_host::ComPortType.SetValue((COMPORT_TYPE)RandomRange(0, (uint8_t)COMPORT_TYPE::MAX));
    sys_host::BatteryNum.SetValue(RandomRange(1, 5));
    sys_host::SerialNum.SetValue(GenerateSerialNumber());

    sys_gui::StrikeNum.SetValue(0);
    sys_gui::TimeCycle.SetValue(TIMECYCLE_0);
    sys_gui::TimeClock.SetValue(std::make_pair(2, 0));
    sys_gui::StrikeNum.SetValue(0);
    sys_gui::IsSuccess.SetValue(false);

    AttachConsoleWindow();

    std::thread([]() {
        std::cout << "===== Dummy Data Initialized =====\n";
        std::cout << "LabelIndicator: " << map_LABEL_INDICATOR[sys_host::LabelIndicator.GetValue()] << "\n";
        std::cout << "BatteryType: " << map_BATTERY_TYPE[sys_host::BatteryType.GetValue()] << "\n";
        std::cout << "ComPortType: " << map_COMPORT_TYPE[sys_host::ComPortType.GetValue()] << "\n";
        std::cout << "BatteryNum: " << std::to_string(sys_host::BatteryNum.GetValue()) << "\n";
        std::cout << "SerialNum: " << sys_host::SerialNum.GetValue() << "\n";
        std::cout << "==================================\n";

        RunFakeTimer(std::get<MINUTE_POS>(sys_gui::TimeClock.GetValue()));
        }).detach();

    std::thread([]() {
        while (sys_gui::StrikeNum.GetValue() != 3)
        {
            if (sys_gui::StrikeState.GetValue())
            {
                sys_gui::StrikeNum.SetValue(sys_gui::StrikeNum.GetValue() + 1);

                switch (sys_gui::StrikeNum.GetValue())
                {
                case 0:
                    sys_gui::TimeCycle.SetValue(TIMECYCLE_0);
                    break;
                case 1:
                    sys_gui::TimeCycle.SetValue(TIMECYCLE_1);
                    break;
                case 2:
                    sys_gui::TimeCycle.SetValue(TIMECYCLE_2);
                    break;
                default:
                    break;
                }

                sys_gui::StrikeState.SetValue(false);
            }
            ::Sleep(100);
        }
        }).detach();
}

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    ::lv_init();

    int32_t zoom_level = 100;
    bool allow_dpi_override = false;
    bool simulator_mode = false;
    lv_display_t* display = ::lv_windows_create_display(
        L"LVGL Windows Application Display",
        320,
        240,
        zoom_level,
        allow_dpi_override,
        simulator_mode);
    if (!display)
    {
        return -1;
    }

    HWND window_handle = ::lv_windows_get_display_window_handle(display);
    if (!window_handle)
    {
        return -1;
    }

    HICON icon_handle = ::LoadIconW(
        hInstance,
        MAKEINTRESOURCE(IDI_LVGL_WINDOWS));
    if (icon_handle)
    {
        ::SendMessageW(
            window_handle,
            WM_SETICON,
            TRUE,
            (LPARAM)icon_handle);
        ::SendMessageW(
            window_handle,
            WM_SETICON,
            FALSE,
            (LPARAM)icon_handle);
    }

    lv_indev_t* pointer_indev = ::lv_windows_acquire_pointer_indev(display);
    if (!pointer_indev)
    {
        return -1;
    }

    lv_indev_t* keypad_indev = ::lv_windows_acquire_keypad_indev(display);
    if (!keypad_indev)
    {
        return -1;
    }

    lv_indev_t* encoder_indev = ::lv_windows_acquire_encoder_indev(display);
    if (!encoder_indev)
    {
        return -1;
    }

    ui_init();

    InitCDataFromFakeTimer();

    Init();

    while (true)
    {
        ::lv_timer_handler();
        AutoUpdate();
        UpdateAll();
        ::Sleep(10);
    }

    lv_deinit();

    ::FreeConsole();

    return 0;
}
