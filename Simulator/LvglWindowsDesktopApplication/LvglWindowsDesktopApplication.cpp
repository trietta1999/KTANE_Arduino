#include <Windows.h>
#include <thread>
#include <LvglWindowsIconResource.h>

#include "lvgl/lvgl.h"
#include "ui.h"
#include "CommonData.h"
#include "CommonLibrary.h"

std::wstring Str2Wstr(const std::string& str)
{
    int size_needed = ::MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo(size_needed, 0);
    ::MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

void InitCDataFromFakeTimer()
{
    uint8_t seed = time(0);
    srand(seed);

    RandomSeed.SetValue(seed);
    LabelIndicator.SetValue((LABEL_INDICATOR)RandomRange(0, (uint8_t)LABEL_INDICATOR::MAX));
    BatteryType.SetValue((BATTERY_TYPE)RandomRange(0, (uint8_t)BATTERY_TYPE::MAX));
    ComPortType.SetValue((COMPORT_TYPE)RandomRange(0, (uint8_t)COMPORT_TYPE::MAX));
    BatteryNum.SetValue(RandomRange(1, 5));
    SerialNum.SetValue(GenerateSerialNumber());

    std::thread([]() {
        wchar_t msg[1000];
        wsprintfW(msg, L"\
            LabelIndicator: %s\n\
            BatteryType: %s\n\
            ComPortType: %s\n\
            BatteryNum: %d\n\
            SerialNum: %s\n\
        ",
            Str2Wstr(map_LABEL_INDICATOR[LabelIndicator.GetValue()]).c_str(),
            Str2Wstr(map_BATTERY_TYPE[BatteryType.GetValue()]).c_str(),
            Str2Wstr(map_COMPORT_TYPE[ComPortType.GetValue()]).c_str(),
            BatteryNum.GetValue(),
            Str2Wstr(SerialNum.GetValue()).c_str()
        );

        auto r = MessageBox(nullptr, msg, L"Dummy data", MB_OK);

        if (r == IDOK)
        {
            ::ExitProcess(0);
        }
        }).detach(); // detach để nó tự chạy và tự thoát
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

    while (1)
    {
        AutoUpdate();
        UpdateAll();
        uint32_t time_till_next = ::lv_timer_handler();
        ::Sleep(time_till_next);
    }

    lv_deinit();
    return 0;
}
