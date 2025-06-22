#include <windows.h>
#include <CppUnitTest.h>
#include "ui/ui.h"
#include "CommonData.h"
#include "CommonLibrary.h"
#include "CommonService.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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
        ProcessRequest(hwnd, wParam, jsonDoc);
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

        ProcessRequest(hwnd, wParam, jsonDoc);
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

//TEST_CLASS(Service_Test)
//{
//public:
//    TEST_CLASS_INITIALIZE(TESTCLASS_Init)
//    {
//        sys_host::TimeClock.SetValue(std::make_pair(2, 3));
//        sys_host::RandomSeed.SetValue(123456);
//        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::BOB);
//        sys_host::BatteryType.SetValue(BATTERY_TYPE::AA);
//        sys_host::ComPortType.SetValue(COMPORT_TYPE::DVID);
//        sys_host::BatteryNum.SetValue(2);
//        sys_host::SerialNum.SetValue("ABCDEFGHI2");
//        sys_host::StrikeNum.SetValue(2);
//        sys_host::StrikeState.SetValue(false);
//        sys_gui::IsStarted.SetValue(true);
//        sys_gui::ModuleStatusMap.SetValue({
//            { "A", MODULE_STATUS::ENABLE },
//            { "B", MODULE_STATUS::DISABLE },
//            });
//
//        lv_init();
//        lv_display_t* display = ::lv_windows_create_display(mapWstr_MODULE_NAME[MODULE_NAME::HostTimer].c_str(), 320, 240, 100, false, false);
//        HWND window_handle = ::lv_windows_get_display_window_handle(display);
//        ui_init();
//        OriginalWndProc = (WNDPROC)::SetWindowLongPtr(window_handle, GWLP_WNDPROC, (LONG_PTR)MyNewWinProc);
//    }
//
//    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
//    {
//        lv_deinit();
//    }
//
//    TEST_METHOD(TEST_ProcessRequest_WM_TIMER_GET)
//    {
//        auto jsonDoc = CommonGetRequest(WM_TIMER_GET);
//
//        Assert::IsTrue(jsonDoc["minute"] == (uint8_t)2);
//        Assert::IsTrue(jsonDoc["second"] == (uint8_t)3);
//    }
//
//    TEST_METHOD(TEST_ProcessRequest_WM_STRIKENUM_GET)
//    {
//        auto jsonDoc = CommonGetRequest(WM_STRIKENUM_GET);
//
//        Assert::IsTrue(jsonDoc[STR(StrikeNum)] == (uint8_t)2);
//    }
//
//    TEST_METHOD(TEST_ProcessRequest_WM_STRIKESTATE_SET)
//    {
//        CommonGetRequest(WM_STRIKESTATE_SET);
//
//        Assert::IsTrue(sys_host::StrikeState.GetValue() == true);
//    }
//
//    TEST_METHOD(TEST_ProcessRequest_WM_SYSINIT_GET)
//    {
//        auto jsonDoc = CommonGetRequest(WM_SYSINIT_GET);
//
//        Assert::IsTrue(jsonDoc[STR(RandomSeed)] == (uint32_t)123456);
//        Assert::IsTrue(jsonDoc[STR(LabelIndicator)] == (uint8_t)LABEL_INDICATOR::BOB);
//        Assert::IsTrue(jsonDoc[STR(BatteryType)] == (uint8_t)BATTERY_TYPE::AA);
//        Assert::IsTrue(jsonDoc[STR(ComPortType)] == (uint8_t)COMPORT_TYPE::DVID);
//        Assert::IsTrue(jsonDoc[STR(BatteryNum)] == (uint8_t)2);
//        Assert::IsTrue(jsonDoc[STR(SerialNum)] == "ABCDEFGHI2");
//        Assert::IsTrue(jsonDoc[STR(StrikeNum)] == (uint8_t)2);
//        Assert::IsTrue(jsonDoc[STR(IsStarted)] == true);
//    }
//
//    TEST_METHOD(TEST_ProcessRequest_WM_STOP_ALL)
//    {
//        auto jsonDoc = CommonGetRequest(WM_STOP_ALL);
//
//        Assert::IsTrue(jsonDoc["stop"] == true);
//    }
//
//    TEST_METHOD(TEST_ProcessRequest_WM_START_1)
//    {
//        JsonDocument jsonDocIn;
//        jsonDocIn["module"] = "A";
//
//        auto jsonDoc = CommonGetRequestWithData(WM_START, jsonDocIn);
//
//        Assert::IsTrue(jsonDoc["module"] == jsonDocIn["module"]);
//        Assert::IsTrue(jsonDoc["status"] == (uint8_t)MODULE_STATUS::ENABLE);
//    }
//
//    TEST_METHOD(TEST_ProcessRequest_WM_START_2)
//    {
//        JsonDocument jsonDocIn;
//        jsonDocIn["module"] = "B";
//
//        auto jsonDoc = CommonGetRequestWithData(WM_START, jsonDocIn);
//
//        Assert::IsTrue(jsonDoc["module"] == jsonDocIn["module"]);
//        Assert::IsTrue(jsonDoc["status"] == (uint8_t)MODULE_STATUS::DISABLE);
//    }
//
//    TEST_METHOD(TEST_ProcessRequest_WM_READY)
//    {
//        auto jsonDoc = CommonGetRequest(WM_READY);
//
//        Assert::IsTrue(jsonDoc["ready"] == true);
//    }
//};
