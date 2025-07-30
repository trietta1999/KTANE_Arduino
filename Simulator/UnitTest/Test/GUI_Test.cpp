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
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();

        delete answerTimer;
        delete commentTimer;
        delete completeTimer;
        delete countdownTimer;
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Cleanup)
    {
        if (answerTimer->textTypingTimer)
        {
            lv_timer_del(answerTimer->textTypingTimer);
            answerTimer->textTypingTimer = nullptr;
        }

        if (commentTimer->textTypingTimer)
        {
            lv_timer_del(commentTimer->textTypingTimer);
            commentTimer->textTypingTimer = nullptr;
        }

        if (completeTimer->textTypingTimer)
        {
            lv_timer_del(completeTimer->textTypingTimer);
            completeTimer->textTypingTimer = nullptr;
        }

        if (countdownTimer->countdownTimer)
        {
            lv_timer_del(countdownTimer->countdownTimer);
            countdownTimer->countdownTimer = nullptr;
        }
    }

    TEST_METHOD(TEST_OnButtonClick_Question1_Y)
    {
        // Init data
        CurrentQuestion.SetValue(listQuestion[0]);

        // Init and activate module
        InitQuestion(false);

        // Simulate button click
        lv_event_t e = { 0 };
        e.current_target = ui_btnYes;
        OnButtonClick(&e);

        // Dummy timer sequence
        answerTimer->outputCondition = true;
        AutoUpdate();
        completeTimer->outputCondition = true;
        AutoUpdate();

        Assert::IsTrue(moduleActivateState == false);
    }

    TEST_METHOD(TEST_OnButtonClick_Question1_N)
    {
        // Init data
        CurrentQuestion.SetValue(listQuestion[0]);

        // Init and activate module
        InitQuestion(false);

        // Simulate button click
        lv_event_t e = { 0 };
        e.current_target = ui_btnNo;
        OnButtonClick(&e);

        // Dummy timer sequence
        answerTimer->outputCondition = true;
        AutoUpdate();
        commentTimer->outputCondition = true;
        AutoUpdate();

        Assert::IsTrue(errorState == false);
        Assert::IsTrue(moduleActivateState == true);
    }

    TEST_METHOD(TEST_OnButtonClick_Question2_N)
    {
        // Init data
        CurrentQuestion.SetValue(listQuestion[1]);

        // Init and activate module
        InitQuestion(false);

        // Simulate button click
        lv_event_t e = { 0 };
        e.current_target = ui_btnNo;
        OnButtonClick(&e);

        // Dummy timer sequence
        answerTimer->outputCondition = true;
        AutoUpdate();
        completeTimer->outputCondition = true;
        AutoUpdate();

        Assert::IsTrue(moduleActivateState == false);
    }

    TEST_METHOD(TEST_OnButtonClick_Question2_Y)
    {
        // Init data
        CurrentQuestion.SetValue(listQuestion[1]);

        // Init and activate module
        InitQuestion(false);

        // Simulate button click
        lv_event_t e = { 0 };
        e.current_target = ui_btnYes;
        OnButtonClick(&e);

        // Dummy timer sequence
        answerTimer->outputCondition = true;
        AutoUpdate();
        commentTimer->outputCondition = true;
        AutoUpdate();

        Assert::IsTrue(moduleActivateState == true);
    }

    TEST_METHOD(TEST_Timeout)
    {
        // Init data
        CurrentQuestion.SetValue(listQuestion[0]);

        // Init and activate module
        InitQuestion(false);

        // Start countdown timer
        countdownTimer->StartTimer(ui_lblTimer, 1);

        // Stop coutdown
        countdownTimer->timeOut = true;

        // Update GUI
        AutoUpdate();

        Assert::IsTrue(moduleActivateState == false);
    }
};
