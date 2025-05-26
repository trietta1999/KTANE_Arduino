#pragma warning(disable : 4244)

#include <Windows.h>
#include <thread>
#include <iostream>
#include <iomanip>
#include <LvglWindowsIconResource.h>

#include "lvgl/lvgl.h"
#include "ui/ui.h"
#include "CommonData.h"
#include "CommonService.h"
#include "CommonLibrary.h"

WNDPROC OriginalWndProc = NULL;
HWND ClientHandle = NULL;

LRESULT CALLBACK MyNewWinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SET_CLIENT_HANDLE:
    {
        HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM);
        if (!hMapFile)
        {
            return FALSE;
        }

        LPVOID pBuffer = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
        if (!pBuffer)
        {
            CloseHandle(hMapFile);
            return FALSE;
        }

        auto receivedJsonString = (const char*)pBuffer;
        if (!receivedJsonString)
        {
            UnmapViewOfFile(pBuffer);
            CloseHandle(hMapFile);
            return FALSE;
        }

        JsonDocument jsonDoc;
        deserializeJson(jsonDoc, receivedJsonString);

        UnmapViewOfFile(pBuffer);

        if (!wParam)
        {
            CloseHandle(hMapFile);
        }

        const char* clientName = jsonDoc["client_name"];
        ClientHandle = ::FindWindowA(NULL, clientName);

        if (!ClientHandle)
        {
            return FALSE;
        }
    }
    break;

    case WM_REQUEST:
    {
        JsonDocument jsonDoc;
        ProcessRequest(ClientHandle, wParam, jsonDoc);
    }
    break;

    case WM_REQUEST_WITH_DATA:
    {
        HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM);
        if (!hMapFile)
        {
            return FALSE;
        }

        LPVOID pBuffer = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
        if (!pBuffer)
        {
            CloseHandle(hMapFile);
            return FALSE;
        }

        auto receivedJsonString = (const char*)pBuffer;
        if (!receivedJsonString)
        {
            UnmapViewOfFile(pBuffer);
            CloseHandle(hMapFile);
            return FALSE;
        }

        JsonDocument jsonDoc;
        deserializeJson(jsonDoc, receivedJsonString);

        UnmapViewOfFile(pBuffer);
        CloseHandle(hMapFile);

        ProcessRequest(ClientHandle, wParam, jsonDoc);
    }
    break;

    case WM_RESPONSE:
    {
        HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, SHARED_MEM);
        if (!hMapFile)
        {
            return FALSE;
        }

        LPVOID pBuffer = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUFFER_SIZE);
        if (!pBuffer)
        {
            CloseHandle(hMapFile);
            return FALSE;
        }

        auto receivedJsonString = (const char*)pBuffer;
        if (!receivedJsonString)
        {
            UnmapViewOfFile(pBuffer);
            CloseHandle(hMapFile);
            return FALSE;
        }

        JsonDocument jsonDoc;
        deserializeJson(jsonDoc, receivedJsonString);
        sys_host::JsonResponse.SetValue(jsonDoc);

        UnmapViewOfFile(pBuffer);
        CloseHandle(hMapFile);
    }
    break;

    case WM_QUIT:
    case WM_DESTROY:
    case WM_NCDESTROY:
        ::SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)OriginalWndProc);
        break;

    default:
        break;
    }

    return CallWindowProc(OriginalWndProc, hwnd, uMsg, wParam, lParam);
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
        CLIENT_NAME,
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

    OriginalWndProc = (WNDPROC)::SetWindowLongPtr(window_handle, GWLP_WNDPROC, (LONG_PTR)MyNewWinProc);
    if (!OriginalWndProc)
    {
        return -1;
    }

    // Create UI
    ui_init();

    // Init service
    InitData();

    // Init GUI
    Init();

    while (true)
    {
        ::lv_timer_handler();
        ProcessData();
        AutoUpdate();
        UpdateAll();
        ::Sleep(10);
    }

    lv_deinit();

    ::FreeConsole();

    return 0;
}
