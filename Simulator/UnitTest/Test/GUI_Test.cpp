#include "CppUnitTest.h"
#include "ui/ui.h"
#include "ui/ui_events.cpp"
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

        Init();
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Cleanup)
    {
        sys_gui::SuccessState.SetValue(INCORRECT);
    }

#pragma region Test_3Wire
    TEST_METHOD(TEST_OnWireSelect_3wire_1)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLUE });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect2;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_3wire_2)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::WHITE });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect3;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_3wire_3)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect2;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_3wire_4)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect3;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
#pragma endregion

#pragma region Test_4Wire
    TEST_METHOD(TEST_OnWireSelect_4wire_1)
    {
        sys_host::SerialNum.SetValue("ABCDEF5");
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect4;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_4wire_2)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::YELLOW });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect2;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_4wire_3)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::YELLOW });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect1;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_4wire_4)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::YELLOW });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect4;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_4wire_5)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::BLACK });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect2;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
#pragma endregion

#pragma region Test_5Wire
    TEST_METHOD(TEST_OnWireSelect_5wire_1)
    {
        sys_host::SerialNum.SetValue("ABCDEF5");
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::BLACK });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect4;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_5wire_2)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::RED });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect1;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_5wire_3)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::RED });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect2;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_5wire_4)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::RED });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect1;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
#pragma endregion

#pragma region Test_6Wire
    TEST_METHOD(TEST_OnWireSelect_6wire_1)
    {
        sys_host::SerialNum.SetValue("ABCDEF5");
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::WHITE });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect3;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_6wire_2)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::WHITE, WIRECOLOR_TYPE::WHITE });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect4;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_6wire_3)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::WHITE });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect6;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnWireSelect_6wire_4)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::WHITE, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::WHITE });
        WireModule();

        lv_event_t e = { 0 };
        e.current_target = ui_btnSelect4;

        OnWireSelect(&e);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
#pragma endregion
};
