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

#pragma region Test_3Wire
    TEST_METHOD(TEST_OnWireSelect_3wire_1)
    {
        libraryTest->TEST_WireModule_3wire_1();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect2;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_3wire_2)
    {
        libraryTest->TEST_WireModule_3wire_2();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect3;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_3wire_3)
    {
        libraryTest->TEST_WireModule_3wire_3();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect2;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_3wire_4)
    {
        libraryTest->TEST_WireModule_3wire_4();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect3;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
#pragma endregion

#pragma region Test_4Wire
    TEST_METHOD(TEST_OnWireSelect_4wire_1)
    {
        libraryTest->TEST_WireModule_4wire_1();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect4;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_4wire_2)
    {
        libraryTest->TEST_WireModule_4wire_2();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect2;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_4wire_3)
    {
        libraryTest->TEST_WireModule_4wire_3();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect1;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_4wire_4)
    {
        libraryTest->TEST_WireModule_4wire_4();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect4;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_4wire_5)
    {
        libraryTest->TEST_WireModule_4wire_5();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect2;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
#pragma endregion

#pragma region Test_5Wire
    TEST_METHOD(TEST_OnWireSelect_5wire_1)
    {
        libraryTest->TEST_WireModule_5wire_1();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect4;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_5wire_2)
    {
        libraryTest->TEST_WireModule_5wire_2();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect1;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_5wire_3)
    {
        libraryTest->TEST_WireModule_5wire_3();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect2;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_5wire_4)
    {
        libraryTest->TEST_WireModule_5wire_4();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect1;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
#pragma endregion

#pragma region Test_6Wire
    TEST_METHOD(TEST_OnWireSelect_6wire_1)
    {
        libraryTest->TEST_WireModule_6wire_1();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect3;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_6wire_2)
    {
        libraryTest->TEST_WireModule_6wire_2();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect4;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_6wire_3)
    {
        libraryTest->TEST_WireModule_6wire_3();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect6;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_6wire_4)
    {
        libraryTest->TEST_WireModule_6wire_4();

        lv_event_t e = { 0 };
        e.current_target = ui_swSelect4;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
#pragma endregion
};
