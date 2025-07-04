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

        // Init GUI
        Init();

        CurrentStage.SetValue(1);
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Cleanup)
    {
        regenerate = false;
        isIncorrectButton = false;
        CurrentStage.SetValue(1);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_1)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_YES, 3);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button1;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_YES);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_2)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_FIRST, 2);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button5;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_MIDDLE);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_3)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_DISPLAY, 6);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button6;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_LEFT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_4)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_OKAY, 2);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button5;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_MIDDLE);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_5)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_SAYS, 6);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button6;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_LEFT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_6)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_NOTHING, 3);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button1;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_YES);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_7)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_EMPTY, 5);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button3;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_READY);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_8)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_BLANK, 4);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button4;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_WHAT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_9)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_NO, 6);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button6;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_LEFT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_10)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_LED, 3);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button1;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_YES);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_11)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_LEED, 6);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button6;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_LEFT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_12)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_READ, 4);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button4;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_WHAT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_13)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_RED, 4);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button4;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_WHAT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_14)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_REED, 5);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button3;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_READY);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_15)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_LEED, 5);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button3;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_READY);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_16)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_HOLD_ON, 6);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button6;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_LEFT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_17)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_YOU, 4);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button4;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_WHAT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_18)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_YOU_ARE, 6);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button6;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_LEFT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_19)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_YOUR, 4);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button4;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_WHAT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_20)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_YOURE, 4);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button4;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_WHAT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_21)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_UR, 1);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button2;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_OKAY);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_22)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_THERE, 6);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button6;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_LEFT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_23)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_THEYRE, 5);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button3;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_READY);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_24)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_THEIR, 4);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button4;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_WHAT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_25)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_THEY_ARE, 3);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button1;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_YES);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_26)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_SEE, 6);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button6;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_LEFT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_27)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_C, 2);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button5;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_MIDDLE);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_28)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_CEE, 6);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button6;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_LEFT);
        Assert::IsTrue(CurrentStage.GetValue() == 2);
    }

    TEST_METHOD(TESTMETHOD_OnButtonClick_29)
    {
        displayInfo = std::make_tuple(TEXT_DISPLAY::E_YOUR, 4);
        listTextLabel = {
            TEXT_LABEL::E_YES,
            TEXT_LABEL::E_OKAY,
            TEXT_LABEL::E_READY,
            TEXT_LABEL::E_WHAT,
            TEXT_LABEL::E_MIDDLE,
            TEXT_LABEL::E_LEFT,
        };
        lv_event_t e = { 0 };
        e.current_target = ui_Button3;

        AutoUpdate();
        OnButtonClick(&e);

        Assert::IsTrue(CorrectTextLabel.GetValue() == TEXT_LABEL::E_WHAT);
        Assert::IsTrue(CurrentStage.GetValue() == 1);
        Assert::IsTrue(isIncorrectButton == true);
    }
#pragma endregion
};
