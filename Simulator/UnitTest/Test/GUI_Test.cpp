#include "CppUnitTest.h"
#include "CommonData.h"
#include "ui/ui.h"
#include "ui/ui_events.h"
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

#pragma region GUI library test
    TEST_METHOD(TEST_ButtonModule_Case1_1)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::BLUE);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::BLUE);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 4);
    }

    TEST_METHOD(TEST_ButtonModule_Case1_2)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::BLUE);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::WHITE);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 1);
    }

    TEST_METHOD(TEST_ButtonModule_Case1_3)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::BLUE);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::YELLOW);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 5);
    }

    TEST_METHOD(TEST_ButtonModule_Case1_4)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::BLUE);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::RED);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 1);
    }

    TEST_METHOD(TEST_ButtonModule_Case2)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::BLUE);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Detonate);
        StripColor.SetValue(COLOR_TYPE::RED);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_SHORT_CLICKED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 0);
    }

    TEST_METHOD(TEST_ButtonModule_Case3_1)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::WHITE);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::BLUE);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 4);
    }

    TEST_METHOD(TEST_ButtonModule_Case3_2)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::WHITE);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::WHITE);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 1);
    }

    TEST_METHOD(TEST_ButtonModule_Case3_3)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::WHITE);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::YELLOW);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 5);
    }

    TEST_METHOD(TEST_ButtonModule_Case3_4)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::WHITE);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::RED);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 1);
    }

    TEST_METHOD(TEST_ButtonModule_Case4)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::FRK);
        sys_host::BatteryNum.SetValue(3);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::BLUE);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Detonate);
        StripColor.SetValue(COLOR_TYPE::RED);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_SHORT_CLICKED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 0);
    }

    TEST_METHOD(TEST_ButtonModule_Case5_1)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::YELLOW);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::BLUE);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 4);
    }

    TEST_METHOD(TEST_ButtonModule_Case5_2)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::YELLOW);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::WHITE);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 1);
    }

    TEST_METHOD(TEST_ButtonModule_Case5_3)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::YELLOW);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::YELLOW);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 5);
    }

    TEST_METHOD(TEST_ButtonModule_Case5_4)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::YELLOW);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Abort);
        StripColor.SetValue(COLOR_TYPE::RED);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 1);
    }

    TEST_METHOD(TEST_ButtonModule_Case6)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(2);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::RED);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Hold);
        StripColor.SetValue(COLOR_TYPE::RED);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_SHORT_CLICKED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 0);
    }

    TEST_METHOD(TEST_ButtonModule_Case7_1)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(1);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::PINK);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Detonate);
        StripColor.SetValue(COLOR_TYPE::BLUE);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 4);
    }

    TEST_METHOD(TEST_ButtonModule_Case7_2)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(1);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::PINK);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Detonate);
        StripColor.SetValue(COLOR_TYPE::WHITE);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 1);
    }

    TEST_METHOD(TEST_ButtonModule_Case7_3)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(1);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::PINK);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Detonate);
        StripColor.SetValue(COLOR_TYPE::YELLOW);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 5);
    }

    TEST_METHOD(TEST_ButtonModule_Case7_4)
    {
        // Host setting
        sys_host::LabelIndicator.SetValue(LABEL_INDICATOR::CAR);
        sys_host::BatteryNum.SetValue(1);

        // Button setting
        ButtonColor.SetValue(COLOR_TYPE::PINK);
        ButtonLabel.SetValue(BTN_LABEL_TYPE::Detonate);
        StripColor.SetValue(COLOR_TYPE::RED);

        ButtonModule();

        auto correctEvent = CorrectEvent.GetValue();

        Assert::IsTrue(std::get<FIRST_EVENT>(correctEvent) == LV_EVENT_LONG_PRESSED);
        Assert::IsTrue(std::get<SECOND_EVENT>(correctEvent) == LV_EVENT_RELEASED);
        Assert::IsTrue(std::get<SPECIAL_NUM>(correctEvent) == 1);
    }
#pragma endregion

#pragma region GUI operation test
    void SendClickEvent()
    {
        OnButtonRelease(nullptr);
        OnButtonClick(nullptr);
    }

    void SendLongPressEvent()
    {
        OnButtonPress(nullptr);
        OnButtonRelease(nullptr);
    }

    TEST_METHOD(TEST_Operation_Case1_1)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case1_1();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case1_2)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case1_2();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case1_3)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case1_3();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case1_4)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case1_4();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case2)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case2();

        // Button event
        SendClickEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case3_1)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case3_1();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case3_2)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case3_2();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case3_3)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case3_3();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case3_4)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case3_4();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case4)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case4();

        // Button event
        SendClickEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case5_1)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case5_1();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case5_2)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case5_2();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case5_3)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case5_3();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case5_4)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case5_4();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case6)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case6();

        // Button event
        SendClickEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case7_1)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case7_1();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case7_2)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case7_2();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case7_3)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case7_3();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_Operation_Case7_4)
    {
        // Init data
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::TimeClock.SetValue(std::make_pair(12, 45));
        TEST_ButtonModule_Case7_4();

        // Button event
        SendLongPressEvent();
        AutoUpdate();

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
#pragma endregion
};
