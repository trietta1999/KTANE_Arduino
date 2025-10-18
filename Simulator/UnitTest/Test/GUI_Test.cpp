#include "CppUnitTest.h"
#include "ui/ui.h"
#include "ui/ui_events.cpp"
#include "CommonData.h"
#include "Library_Test.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static Library_Test* libraryTest;

TEST_CLASS(GUI_Test)
{
public:
    TEST_CLASS_INITIALIZE(TESTCLASS_Init)
    {
        lv_init();
        lv_windows_create_display(L"", 320, 240, 100, false, false);
        ui_init();

        Init();

        libraryTest = new Library_Test();
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
        delete libraryTest;
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Cleanup)
    {
        sys_gui::SuccessState.SetValue(INCORRECT);
    }
};
