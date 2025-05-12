#include "CppUnitTest.h"
#include "ui/ui.h"
#include "ui/ui_events.h"
#include "CommonData.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(GUI_Test)
{
public:
    TEST_CLASS_INITIALIZE(TESTCLASS_Init)
    {
        lv_init();
        lv_windows_create_display(L"", 320, 240, 100, false, false);
        ui_init();
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
    }
};
