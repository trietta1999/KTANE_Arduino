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

        // Init GUI
        Init();

        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();

        delete countdownTimer;
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Cleanup)
    {
        sys_gui::SuccessState.SetValue(INCORRECT);

        // Delete timer
        if (countdownTimer->countdownTimer)
        {
            lv_timer_del(countdownTimer->countdownTimer);
            countdownTimer->countdownTimer = nullptr;
        }
    }

    TEST_METHOD(TEST_OnKnobClick_UP_1)
    {
        // Init data
        CorrectDirectionType.SetValue(KNOB_DIRECTION_TYPE::UP);
        CurrentPatternIndex.SetValue(0);

        // Init and activate module
        InitModule();

        // Simulate knob click
        while (CurrentDirectionType.GetValue() != CorrectDirectionType.GetValue())
        {
            OnKnobClick(nullptr);
        }

        // Set timeout
        countdownTimer->timeOut = true;

        // Update GUI
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnKnobClick_UP_2)
    {
        // Init data
        CorrectDirectionType.SetValue(KNOB_DIRECTION_TYPE::UP);
        CurrentPatternIndex.SetValue(1);

        // Init and activate module
        InitModule();

        // Simulate knob click
        while (CurrentDirectionType.GetValue() != CorrectDirectionType.GetValue())
        {
            OnKnobClick(nullptr);
        }

        // Set timeout
        countdownTimer->timeOut = true;

        // Update GUI
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnKnobClick_DOWN_1)
    {
        // Init data
        CorrectDirectionType.SetValue(KNOB_DIRECTION_TYPE::DOWN);
        CurrentPatternIndex.SetValue(0);

        // Init and activate module
        InitModule();

        // Simulate knob click
        while (CurrentDirectionType.GetValue() != CorrectDirectionType.GetValue())
        {
            OnKnobClick(nullptr);
        }

        // Set timeout
        countdownTimer->timeOut = true;

        // Update GUI
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnKnobClick_DOWN_2)
    {
        // Init data
        CorrectDirectionType.SetValue(KNOB_DIRECTION_TYPE::DOWN);
        CurrentPatternIndex.SetValue(1);

        // Init and activate module
        InitModule();

        // Simulate knob click
        while (CurrentDirectionType.GetValue() != CorrectDirectionType.GetValue())
        {
            OnKnobClick(nullptr);
        }

        // Set timeout
        countdownTimer->timeOut = true;

        // Update GUI
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnKnobClick_LEFT_1)
    {
        // Init data
        CorrectDirectionType.SetValue(KNOB_DIRECTION_TYPE::LEFT);
        CurrentPatternIndex.SetValue(0);

        // Init and activate module
        InitModule();

        // Simulate knob click
        while (CurrentDirectionType.GetValue() != CorrectDirectionType.GetValue())
        {
            OnKnobClick(nullptr);
        }

        // Set timeout
        countdownTimer->timeOut = true;

        // Update GUI
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnKnobClick_LEFT_2)
    {
        // Init data
        CorrectDirectionType.SetValue(KNOB_DIRECTION_TYPE::LEFT);
        CurrentPatternIndex.SetValue(1);

        // Init and activate module
        InitModule();

        // Simulate knob click
        while (CurrentDirectionType.GetValue() != CorrectDirectionType.GetValue())
        {
            OnKnobClick(nullptr);
        }

        // Set timeout
        countdownTimer->timeOut = true;

        // Update GUI
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnKnobClick_RIGHT_1)
    {
        // Init data
        CorrectDirectionType.SetValue(KNOB_DIRECTION_TYPE::RIGHT);
        CurrentPatternIndex.SetValue(0);

        // Init and activate module
        InitModule();

        // Simulate knob click
        while (CurrentDirectionType.GetValue() != CorrectDirectionType.GetValue())
        {
            OnKnobClick(nullptr);
        }

        // Set timeout
        countdownTimer->timeOut = true;

        // Update GUI
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_OnKnobClick_RIGHT_2)
    {
        // Init data
        CorrectDirectionType.SetValue(KNOB_DIRECTION_TYPE::RIGHT);
        CurrentPatternIndex.SetValue(1);

        // Init and activate module
        InitModule();

        // Simulate knob click
        while (CurrentDirectionType.GetValue() != CorrectDirectionType.GetValue())
        {
            OnKnobClick(nullptr);
        }

        // Set timeout
        countdownTimer->timeOut = true;

        // Update GUI
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
};
