#include "CppUnitTest.h"
#include "CommonData.h"
#include "ui/ui_events.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(GUI_Test)
{
public:
    TEST_CLASS_INITIALIZE(TESTCLASS_Init)
    {
        lv_init();
        lv_windows_create_display(L"", 320, 240, 100, false, false);
        ui_init();

        // Choose random column
        ColumnIndex.SetValue(1);

        // Get random 4 item (keep ordering) in column
        OrderIndex.SetValue({ 2, 6, 3, 0 });

        // Init GUI
        Init();
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
    }

    void TESTMETHOD_Cleanup()
    {
        isCorrectKey = false;
        isIncorrect = false;
        currentKeyIndex = 0;
        currentKeypad = nullptr;
    }

    void TESTMETHOD_Cleanup1()
    {
        isCorrectKey = false;
        isIncorrect = false;
        currentKeypad = nullptr;
    }

    TEST_METHOD(TEST_OnButtonKeypadClick_1) // Incorrect button order
    {
        lv_event_t e = { 0 };
        e.current_target = ui_btnKey1;

        OnButtonKeypadClick(&e);

        Assert::IsTrue(isIncorrect == true);
        Assert::IsTrue(isCorrectKey == false);

        TESTMETHOD_Cleanup();
    }

    TEST_METHOD(TEST_OnButtonKeypadClick_2) // Incorrect button order
    {
        lv_event_t e = { 0 };
        e.current_target = ui_btnKey2;

        OnButtonKeypadClick(&e);

        Assert::IsTrue(isIncorrect == true);
        Assert::IsTrue(isCorrectKey == false);

        TESTMETHOD_Cleanup();
    }

    TEST_METHOD(TEST_OnButtonKeypadClick_3) // Incorrect button order
    {
        lv_event_t e = { 0 };
        e.current_target = ui_btnKey3;

        OnButtonKeypadClick(&e);

        Assert::IsTrue(isIncorrect == true);
        Assert::IsTrue(isCorrectKey == false);

        TESTMETHOD_Cleanup();
    }

    TEST_METHOD(TEST_OnButtonKeypadClick_4) // Correct button order
    {
        lv_event_t e = { 0 };
        e.current_target = ui_btnKey4;

        OnButtonKeypadClick(&e);

        Assert::IsTrue(isIncorrect == false);
        Assert::IsTrue(isCorrectKey == true);

        TESTMETHOD_Cleanup1();
    }

    TEST_METHOD(TEST_OnButtonKeypadClick_5) // Correct button order
    {
        lv_event_t e = { 0 };
        e.current_target = ui_btnKey1;

        OnButtonKeypadClick(&e);

        Assert::IsTrue(isIncorrect == false);
        Assert::IsTrue(isCorrectKey == true);

        TESTMETHOD_Cleanup1();
    }

    TEST_METHOD(TEST_OnButtonKeypadClick_6) // Incorrect button order
    {
        lv_event_t e = { 0 };
        e.current_target = ui_btnKey2;

        OnButtonKeypadClick(&e);

        Assert::IsTrue(isIncorrect == true);
        Assert::IsTrue(isCorrectKey == false);

        TESTMETHOD_Cleanup1();
    }

    TEST_METHOD(TEST_OnButtonKeypadClick_7) // Correct button order
    {
        lv_event_t e = { 0 };
        e.current_target = ui_btnKey3;

        OnButtonKeypadClick(&e);

        Assert::IsTrue(isIncorrect == false);
        Assert::IsTrue(isCorrectKey == true);

        TESTMETHOD_Cleanup1();
    }

    TEST_METHOD(TEST_OnButtonKeypadClick_8) // Correct button order
    {
        lv_event_t e = { 0 };
        e.current_target = ui_btnKey2;

        OnButtonKeypadClick(&e);

        Assert::IsTrue(isIncorrect == false);
        Assert::IsTrue(isCorrectKey == true);

        TESTMETHOD_Cleanup1();
    }
};
