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
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Cleanup)
    {
        sys_gui::SuccessState.SetValue(INCORRECT);
        CurrentPanelIndex.SetValue(0);
        CurrentStage.SetValue(0);

        listPanelValidSum.clear();
        currentValidSum = 0;
        currentPanelValidSum = 0;
        validSum = 0;
    }

    TEST_METHOD(TESTMETHOD_RedRuleCheck)
    {
#pragma region RedRuleCheck_Init
        listPanel = {
            // Subpanel 1
            {
                { 1, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::RED, true  },
                { 1, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::RED, true  },
                { 1, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
            },
            // Subpanel 2
            {
                { 2, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 2, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 2, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 2, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::RED, true  },
                { 2, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 2, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::RED, true  },
                { 2, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 2, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::RED, true  },
                { 2, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
            },
            // Subpanel 3
            {
                { 3, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::RED, true  },
                { 3, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::RED, true  },
                { 3, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
            },
            // Subpanel 4
            {
                { 4, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::RED, true  },
                { 4, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::RED, true  },
                { 4, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
            },
        };

        std::vector<WIRECOLOR_TYPE> colorList(9, WIRECOLOR_TYPE::RED);
        WireColorList.SetValue(colorList);

        Init();

        lv_event_t e = { 0 };
#pragma endregion

#pragma region RedRuleCheck_Panel_1
        e.current_target = ui_bar1C;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)1);

        e.current_target = ui_bar2B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)2);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)2);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)1);
        Assert::AreEqual(listPanelValidSum[0].second, true);
#pragma endregion

#pragma region RedRuleCheck_Panel_2
        e.current_target = ui_bar2A;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)3);

        e.current_target = ui_bar2C;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)4);

        e.current_target = ui_bar3B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)3);
        Assert::AreEqual(currentValidSum, (uint8_t)5);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)3);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)2);
        Assert::AreEqual(listPanelValidSum[1].second, true);
#pragma endregion

#pragma region RedRuleCheck_Panel_3
        e.current_target = ui_bar1C;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)6);

        e.current_target = ui_bar2B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)7);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)4);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)3);
        Assert::AreEqual(listPanelValidSum[2].second, true);
#pragma endregion

#pragma region RedRuleCheck_Panel_4
        e.current_target = ui_bar3A;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)8);

        e.current_target = ui_bar3B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)9);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)5);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)4);
        Assert::AreEqual(listPanelValidSum[3].second, true);
#pragma endregion

        AutoUpdate();
        Assert::AreEqual(sys_gui::SuccessState.GetValue(), (uint8_t)STATE_CHECKED);
    }

    TEST_METHOD(TESTMETHOD_BlueRuleCheck)
    {
#pragma region BlueRuleCheck_Init
        listPanel = {
            // Subpanel 1
            {
                { 1, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::BLUE, true },
                { 1, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::BLUE, true },
                { 1, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 1, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
            },
            // Subpanel 2
            {
                { 2, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 2, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::BLUE, true },
                { 2, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 2, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::BLUE, true },
                { 2, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::BLUE, true },
                { 2, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 2, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 2, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 2, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
            },
            // Subpanel 3
            {
                { 3, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::BLUE, true },
                { 3, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::BLUE, true },
                { 3, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 3, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
            },
            // Subpanel 4
            {
                { 4, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::BLUE, true },
                { 4, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::BLUE, true },
                { 4, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false },
                { 4, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false },
            },
        };

        std::vector<WIRECOLOR_TYPE> colorList(9, WIRECOLOR_TYPE::BLUE);
        WireColorList.SetValue(colorList);

        Init();

        lv_event_t e = { 0 };
#pragma endregion

#pragma region BlueRuleCheck_Panel_1
        e.current_target = ui_bar1B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)1);

        e.current_target = ui_bar2A;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)2);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)2);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)1);
        Assert::AreEqual(listPanelValidSum[0].second, true);
#pragma endregion

#pragma region BlueRuleCheck_Panel_2
        e.current_target = ui_bar1B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)3);

        e.current_target = ui_bar2A;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)4);

        e.current_target = ui_bar2B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)3);
        Assert::AreEqual(currentValidSum, (uint8_t)5);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)3);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)2);
        Assert::AreEqual(listPanelValidSum[1].second, true);
#pragma endregion

#pragma region BlueRuleCheck_Panel_3
        e.current_target = ui_bar1B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)6);

        e.current_target = ui_bar2C;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)7);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)4);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)3);
        Assert::AreEqual(listPanelValidSum[2].second, true);
#pragma endregion

#pragma region BlueRuleCheck_Panel_4
        e.current_target = ui_bar2A;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)8);

        e.current_target = ui_bar3A;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)9);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)5);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)4);
        Assert::AreEqual(listPanelValidSum[3].second, true);
#pragma endregion

        AutoUpdate();
        Assert::AreEqual(sys_gui::SuccessState.GetValue(), (uint8_t)STATE_CHECKED);
    }

    TEST_METHOD(TESTMETHOD_BlackRuleCheck)
    {
#pragma region BlackRuleCheck_Init
        listPanel = {
            // Subpanel 1
            {
                { 1, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false  },
                { 1, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false  },
                { 1, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false  },
                { 1, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::BLACK, true },
                { 1, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false  },
                { 1, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::BLACK, true },
                { 1, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false  },
                { 1, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false  },
                { 1, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false  },
            },
            // Subpanel 2
            {
                { 2, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false  },
                { 2, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::BLACK, true },
                { 2, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::BLACK, true },
                { 2, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false  },
                { 2, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::BLACK, true },
                { 2, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false  },
                { 2, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false  },
                { 2, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false  },
                { 2, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false  },
            },
            // Subpanel 3
            {
                { 3, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false  },
                { 3, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false  },
                { 3, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false  },
                { 3, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false  },
                { 3, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::BLACK, true },
                { 3, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false  },
                { 3, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::BLACK, true },
                { 3, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false  },
                { 3, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false  },
            },
            // Subpanel 4
            {
                { 4, STR(ui_bar1A), ui_bar1A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false  },
                { 4, STR(ui_bar1B), ui_bar1B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false  },
                { 4, STR(ui_bar1C), ui_bar1C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::BLACK, true },
                { 4, STR(ui_bar2A), ui_bar2A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false  },
                { 4, STR(ui_bar2B), ui_bar2B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false  },
                { 4, STR(ui_bar2C), ui_bar2C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::BLACK, true },
                { 4, STR(ui_bar3A), ui_bar3A, WIRE_IN_ORDER::A, WIRECOLOR_TYPE::MIN, false  },
                { 4, STR(ui_bar3B), ui_bar3B, WIRE_IN_ORDER::B, WIRECOLOR_TYPE::MIN, false  },
                { 4, STR(ui_bar3C), ui_bar3C, WIRE_IN_ORDER::C, WIRECOLOR_TYPE::MIN, false  },
            },
        };

        std::vector<WIRECOLOR_TYPE> colorList(9, WIRECOLOR_TYPE::BLACK);
        WireColorList.SetValue(colorList);

        Init();

        lv_event_t e = { 0 };
#pragma endregion

#pragma region BlackRuleCheck_Panel_1
        e.current_target = ui_bar2A;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)1);

        e.current_target = ui_bar2C;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)2);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)2);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)1);
        Assert::AreEqual(listPanelValidSum[0].second, true);
#pragma endregion

#pragma region BlackRuleCheck_Panel_2
        e.current_target = ui_bar1B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)3);

        e.current_target = ui_bar1C;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)4);

        e.current_target = ui_bar2B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)3);
        Assert::AreEqual(currentValidSum, (uint8_t)5);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)3);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)2);
        Assert::AreEqual(listPanelValidSum[1].second, true);
#pragma endregion

#pragma region BlackRuleCheck_Panel_3
        e.current_target = ui_bar2B;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)6);

        e.current_target = ui_bar3A;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)7);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)4);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)3);
        Assert::AreEqual(listPanelValidSum[2].second, true);
#pragma endregion

#pragma region BlackRuleCheck_Panel_4
        e.current_target = ui_bar1C;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)1);
        Assert::AreEqual(currentValidSum, (uint8_t)8);

        e.current_target = ui_bar2C;
        OnButtonCutClick(&e);
        Assert::AreEqual(currentPanelValidSum, (uint8_t)2);
        Assert::AreEqual(currentValidSum, (uint8_t)9);

        e.current_target = ui_btnPanelUp;
        OnPanelChange(&e);
        Assert::AreEqual(CurrentPanelIndex.GetValue(), (uint8_t)5);
        Assert::AreEqual(CurrentStage.GetValue(), (uint8_t)4);
        Assert::AreEqual(listPanelValidSum[3].second, true);
#pragma endregion

        AutoUpdate();
        Assert::AreEqual(sys_gui::SuccessState.GetValue(), (uint8_t)STATE_CHECKED);
    }
};
