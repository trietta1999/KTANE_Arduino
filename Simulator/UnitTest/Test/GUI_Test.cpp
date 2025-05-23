#include "CppUnitTest.h"
#include "ui/ui.h"
#include "ui/ui_events.h"
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

    TEST_METHOD(TEST_OnSliderChange)
    {
        lv_slider_set_value(ui_Slider1, 100, LV_ANIM_ON);
        OnSliderChange(NULL);

        Assert::IsTrue(SliderValue.GetValue() == 100);
        Assert::IsTrue(sys_gui::Brightness.GetValue() == 100);
    }

    TEST_METHOD(TEST_OnButtonNormalClick)
    {
        OnButtonNormalClick(NULL);

        Assert::IsTrue(Button2Value.GetValue() == 1);
        Assert::IsTrue(sys_gui::StrikeState.GetValue() == true);
    }

    TEST_METHOD(TEST_OnArcChange)
    {
        lv_arc_set_value(ui_Arc1, 10);
        OnArcChange(NULL);

        Assert::IsTrue(ArcValue.GetValue() == 10);
    }

    TEST_METHOD(TEST_OnCheckboxClick)
    {
        lv_obj_set_state(ui_Checkbox1, 10, true);
        OnCheckboxClick(NULL);

        Assert::IsTrue(CheckboxValue.GetValue() == 10);
    }

    TEST_METHOD(TEST_OnDropdownChange)
    {
        lv_dropdown_set_options(ui_Dropdown1, "One\nTwo\nThree");
        lv_dropdown_set_selected(ui_Dropdown1, 1);
        OnDropdownChange(NULL);

        Assert::IsTrue(DropdownValue.GetValue() == "Two");
    }

    TEST_METHOD(TEST_OnSwitchClick)
    {
        lv_obj_set_state(ui_Switch1, 10, true);
        OnSwitchClick(NULL);

        Assert::IsTrue(SwitchValue.GetValue() == 10);
    }

    TEST_METHOD(TEST_OnRollerChange)
    {
        lv_roller_set_options(ui_Roller1, "One\nTwo\nThree", LV_ROLLER_MODE_NORMAL);
        lv_roller_set_selected(ui_Roller1, 2, LV_ANIM_ON);
        OnRollerChange(NULL);

        Assert::IsTrue(RollerValue.GetValue() == "Three");
    }

    TEST_METHOD(TEST_OnButtonToggleClick)
    {
        lv_obj_set_state(ui_Button2, 10, true);
        OnButtonToggleClick(NULL);

        Assert::IsTrue(Button2Value.GetValue() == 10);
    }
};
