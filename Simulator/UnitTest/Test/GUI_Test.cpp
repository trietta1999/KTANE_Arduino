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

        Init();
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
    }

    TEST_METHOD_INITIALIZE(TESTMETHOD_Init)
    {
        sys_host::StrikeNum.SetValue(0);
        sys_gui::SuccessState.SetValue(INCORRECT);
        sys_host::ModuleStatus.SetValue(false);
        sys_host::ClientName.SetValue("");
        sys_host::TimeCycle.SetValue(TIMECYCLE_0);
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Clean)
    {
        UpdateAll();

        lv_obj_remove_state(ui_cbSettingModule1, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingModule2, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingModule3, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingModule4, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingModule5, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingModule6, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingModule7, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingModule8, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingModule9, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingModule10, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingModule11, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingNeedyModule1, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingNeedyModule2, LV_STATE_CHECKED);
        lv_obj_remove_state(ui_cbSettingNeedyModule3, LV_STATE_CHECKED);
    }

    TEST_METHOD(TEST_CalculateEndlessTimer)
    {
        endlessTimer.startTime = MILLISEC_GET - 91560; // 1m 31s 560ms

        CalculateEndlessTimer();

        auto time = sys_host::EndlessTimeClock.GetValue();

        Assert::AreEqual(std::get<MINUTE_POS>(time), (uint16_t)1);
        Assert::AreEqual(std::get<SECOND_POS>(time), (uint16_t)31);
        Assert::AreEqual(std::get<MILLIS_POS>(time), (uint16_t)560);
    }

    TEST_METHOD(TEST_CalculateCountdownTimer_1)
    {
        countdownTimer.minute = 0;
        countdownTimer.second = 0;

        CalculateCountdownTimer();

        Assert::AreEqual(sys_host::ClientName.GetValue(), std::string("Timeout"));
        Assert::AreEqual(sys_gui::SuccessState.GetValue(), (uint8_t)STATE_UNCHECK);
    }

    TEST_METHOD(TEST_CalculateCountdownTimer_2)
    {
        countdownTimer.minute = 1;
        countdownTimer.second = 1;

        sys_host::StrikeNum.SetValue(STRIKE_NUM_MAX);
        sys_host::ClientName.SetValue(map_MODULE_NAME[MODULE_NAME::Wires]);

        CalculateCountdownTimer();

        Assert::AreEqual(sys_host::ClientName.GetValue(), map_MODULE_NAME[MODULE_NAME::Wires]);
        Assert::AreEqual(sys_gui::SuccessState.GetValue(), (uint8_t)STATE_UNCHECK);
    }

    TEST_METHOD(TEST_CalculateCountdownTimer_3)
    {
        countdownTimer.minute = 1;
        countdownTimer.second = 1;

        sys_gui::SuccessState.SetValue(STATE_CHECKED);

        CalculateCountdownTimer();

        Assert::AreEqual(sys_host::ModuleStatus.GetValue(), false);
    }

    TEST_METHOD(TEST_CalculateCountdownTimer_4)
    {
        countdownTimer.minute = 10;
        countdownTimer.second = 10;
        countdownTimer.startTime = MILLISEC_GET - TIMECYCLE_0;

        CalculateCountdownTimer();

        Assert::AreEqual(countdownTimer.minute, (uint8_t)10);
        Assert::AreEqual(countdownTimer.second, (uint8_t)9);
        Assert::IsTrue(sys_host::TimeClock.GetValue() == std::make_pair(countdownTimer.minute, countdownTimer.second));
    }

    TEST_METHOD(TEST_CalculateCountdownTimer_5)
    {
        countdownTimer.minute = 10;
        countdownTimer.second = 0;
        countdownTimer.startTime = MILLISEC_GET - TIMECYCLE_0;

        CalculateCountdownTimer();

        Assert::AreEqual(countdownTimer.minute, (uint8_t)9);
        Assert::AreEqual(countdownTimer.second, (uint8_t)59);
        Assert::IsTrue(sys_host::TimeClock.GetValue() == std::make_pair(countdownTimer.minute, countdownTimer.second));
    }

    TEST_METHOD(TEST_StrikeStateUpdate_1)
    {
        sys_host::StrikeNum.SetValue(0);
        sys_host::StrikeState.SetValue(true);

        AutoUpdate();

        Assert::AreEqual(sys_host::StrikeNum.GetValue(), (uint8_t)1);
        Assert::AreEqual(sys_host::TimeCycle.GetValue(), (uint16_t)TIMECYCLE_1);
    }

    TEST_METHOD(TEST_StrikeStateUpdate_2)
    {
        sys_host::StrikeNum.SetValue(1);
        sys_host::StrikeState.SetValue(true);

        AutoUpdate();

        Assert::AreEqual(sys_host::StrikeNum.GetValue(), (uint8_t)2);
        Assert::AreEqual(sys_host::TimeCycle.GetValue(), (uint16_t)TIMECYCLE_2);
    }

    TEST_METHOD(TEST_Login_OnTextAreaEdit_1)
    {
        lv_textarea_set_text(ui_TextArea, "12");

        Login_OnTextAreaEdit(NULL);

        auto bgColor = lv_obj_get_style_bg_color(ui_TextArea, LV_PART_MAIN | LV_STATE_DEFAULT);
        auto checkColor = lv_color_hex(COLOR_WHITE);

        Assert::IsTrue(memcmp(&bgColor, &checkColor, sizeof(lv_color_t)) == 0);
    }

    TEST_METHOD(TEST_Login_OnTextAreaEdit_2)
    {
        lv_textarea_set_text(ui_TextArea, "123");

        Login_OnTextAreaEdit(NULL);

        auto bgColor = lv_obj_get_style_bg_color(ui_TextArea, LV_PART_MAIN | LV_STATE_DEFAULT);
        auto checkColor = lv_color_hex(COLOR_RED);

        Assert::IsTrue(memcmp(&bgColor, &checkColor, sizeof(lv_color_t)) == 0);
    }

    TEST_METHOD(TEST_Login_OnTextAreaEdit_3)
    {
        lv_textarea_set_text(ui_TextArea, std::string(VERIFY_CODE).c_str());

        Login_OnTextAreaEdit(NULL);

        auto bgColor = lv_obj_get_style_bg_color(ui_TextArea, LV_PART_MAIN | LV_STATE_DEFAULT);
        auto checkColor = lv_color_hex(COLOR_GREEN);

        Assert::IsTrue(memcmp(&bgColor, &checkColor, sizeof(lv_color_t)) == 0);
    }

    TEST_METHOD(TEST_Login_ModuleSelect_OnCheckboxClick_1)
    {
        lv_obj_add_state(ui_cbSettingModule1, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule2, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule3, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule4, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule5, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingNeedyModule1, LV_STATE_CHECKED);

        ModuleSelect_OnCheckboxClick(NULL);

        Assert::IsTrue((lv_obj_get_state(ui_btnModuleSelectNext) & LV_STATE_DISABLED) != LV_STATE_DISABLED);
    }

    TEST_METHOD(TEST_Login_ModuleSelect_OnCheckboxClick_2)
    {
        lv_obj_add_state(ui_cbSettingModule1, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule2, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule3, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule4, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingNeedyModule1, LV_STATE_CHECKED);

        ModuleSelect_OnCheckboxClick(NULL);

        Assert::IsTrue((lv_obj_get_state(ui_btnModuleSelectNext) & LV_STATE_DISABLED) != LV_STATE_DISABLED);
    }

    TEST_METHOD(TEST_Login_ModuleSelect_OnCheckboxClick_3)
    {
        lv_obj_add_state(ui_cbSettingModule1, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule2, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule3, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule4, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule5, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingNeedyModule1, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingNeedyModule2, LV_STATE_CHECKED);

        ModuleSelect_OnCheckboxClick(NULL);

        Assert::IsTrue((lv_obj_get_state(ui_btnModuleSelectNext) & LV_STATE_DISABLED) == LV_STATE_DISABLED);
    }

    TEST_METHOD(TEST_Login_ModuleSelect_OnButtonNextClick)
    {
        lv_obj_add_state(ui_cbSettingModule1, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule2, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule3, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingModule4, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingNeedyModule1, LV_STATE_CHECKED);
        lv_obj_add_state(ui_cbSettingNeedyModule2, LV_STATE_CHECKED);

        ModuleSelect_OnButtonNextClick(NULL);

        auto moduleStatusMap = sys_gui::ModuleStatusMap.GetValue();

        Assert::IsTrue(moduleStatusMap[map_MODULE_NAME[MODULE_NAME::Wires]] == MODULE_STATUS::ON);
        Assert::IsTrue(moduleStatusMap[map_MODULE_NAME[MODULE_NAME::TheButton]] == MODULE_STATUS::ON);
        Assert::IsTrue(moduleStatusMap[map_MODULE_NAME[MODULE_NAME::Keypads]] == MODULE_STATUS::ON);
        Assert::IsTrue(moduleStatusMap[map_MODULE_NAME[MODULE_NAME::SimonSays]] == MODULE_STATUS::ON);
        Assert::IsTrue(moduleStatusMap[map_MODULE_NAME[MODULE_NAME::VentingGas]] == MODULE_STATUS::ON);
        Assert::IsTrue(moduleStatusMap[map_MODULE_NAME[MODULE_NAME::CapacitorDischarge]] == MODULE_STATUS::ON);
        Assert::IsTrue(moduleStatusMap[map_MODULE_NAME[MODULE_NAME::SystemInfo]] == MODULE_STATUS::ON);

        Assert::IsTrue(moduleStatusMap[map_MODULE_NAME[MODULE_NAME::WhosOnFirst]] == MODULE_STATUS::OFF);
        Assert::IsTrue(moduleStatusMap[map_MODULE_NAME[MODULE_NAME::Memory]] == MODULE_STATUS::OFF);
    }

    TEST_METHOD(TEST_TimerSelect_OnButtonNextClick)
    {
        lv_roller_set_selected(ui_rlSettingMinute, 1, LV_ANIM_OFF); // 5s
        lv_roller_set_selected(ui_rlSettingSecond, 1, LV_ANIM_OFF); // 5s

        TimerSelect_OnButtonNextClick(NULL);

        auto time = sys_host::TimeClock.GetValue();

        Assert::AreEqual(std::get<MINUTE_POS>(time), (uint8_t)5);
        Assert::AreEqual(std::get<SECOND_POS>(time), (uint8_t)5);
        Assert::AreEqual(countdownTimer.minute, (uint8_t)5);
        Assert::AreEqual(countdownTimer.second, (uint8_t)5);
        Assert::AreEqual(settingTimer.minute, (uint8_t)5);
        Assert::AreEqual(settingTimer.second, (uint8_t)5);
    }
};
