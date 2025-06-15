#include "CppUnitTest.h"
#include "CommonData.h"
#include "ui/ui_events.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(GUI_Test)
{
public:
#pragma region Setup_TestClass
    TEST_CLASS_INITIALIZE(TESTCLASS_Init)
    {
        lv_init();
        lv_windows_create_display(L"", 320, 240, 100, false, false);
        ui_init();

        CurrentStage.SetValue(4);

        // Init GUI
        Init();
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Cleanup)
    {

    }
#pragma endregion
};
