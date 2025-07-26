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
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Cleanup)
    {
        sys_gui::SuccessState.SetValue(INCORRECT);
    }

    TEST_METHOD(TEST_Operation_ButtonUp)
    {
        // Init data
        CorrectPassword.SetValue("ABCDE");

        // Init GUI
        Init();

        // Loop each roller
        for (uint8_t i = 0; i < listRollerWithButton.size(); i++)
        {
            // Set object target is button up
            lv_event_t e = { 0 };
            e.current_target = listRollerWithButton[i].second.first;

            // Loop until current letter is correct
            while (true)
            {
                // Simulate button click
                OnButtonClick(&e);

                if (CurrentPassword.GetValue()[i] == CorrectPassword.GetValue()[i])
                {
                    break;
                }
            }
        }

        // Simulate submit
        OnButtonSubmitClick(nullptr);

        Assert::IsTrue(CurrentPassword.GetValue() == CorrectPassword.GetValue());
        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_ButtonDown)
    {
        // Init data
        CorrectPassword.SetValue("QWERT");

        // Init GUI
        Init();

        // Loop each roller
        for (uint8_t i = 0; i < listRollerWithButton.size(); i++)
        {
            // Set object target is button down
            lv_event_t e = { 0 };
            e.current_target = listRollerWithButton[i].second.second;

            // Loop until current letter is correct
            while (true)
            {
                // Simulate button click
                OnButtonClick(&e);

                if (CurrentPassword.GetValue()[i] == CorrectPassword.GetValue()[i])
                {
                    break;
                }
            }
        }

        // Simulate submit
        OnButtonSubmitClick(nullptr);

        Assert::IsTrue(CurrentPassword.GetValue() == CorrectPassword.GetValue());
        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
};
