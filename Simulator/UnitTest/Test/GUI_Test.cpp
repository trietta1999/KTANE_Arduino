#include "CppUnitTest.h"
#include "CommonData.h"
#include "ui/ui_events.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(GUI_Test)
{
public:
#pragma region Setup_TestClass
    decltype(mapColorSequence) mapColorSequence_backup;

    TEST_CLASS_INITIALIZE(TESTCLASS_Init)
    {
        lv_init();
        lv_windows_create_display(L"", 320, 240, 100, false, false);
        ui_init();

        CurrentStage.SetValue(4);
        ColorList.SetValue({ COLOR_TYPE::RED, COLOR_TYPE::BLUE, COLOR_TYPE::GREEN, COLOR_TYPE::YELLOW });

        // Init GUI
        Init();
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Cleanup)
    {
        isIncorrectButton = false;
        currentSelectButtonIndex = 0;

        ResetTable();
    }

    void ChooseTable()
    {
        mapColorSequence_backup = mapColorSequence;

        if (VowelCheck(sys_host::SerialNum.GetValue()))
        {
            mapColorSequence.erase(WITHOUT_VOWEL);
        }
        else
        {
            mapColorSequence.erase(WITH_VOWEL);
        }
    }

    void ResetTable()
    {
        mapColorSequence.clear();
        mapColorSequence = mapColorSequence_backup;
        mapColorSequence_backup.clear();
    }
#pragma endregion

#pragma region Vowel_0_Strike
    void Vowel_0_Strike_Setup()
    {
        sys_host::SerialNum.SetValue("KA2");
        sys_host::StrikeNum.SetValue(0);

        ChooseTable();

        Init();
        AutoUpdate();
    }

    TEST_METHOD(TEST_Vowel_0_Strike_OnButtonKeypadClick_1)
    {
        Vowel_0_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }

    TEST_METHOD(TEST_Vowel_0_Strike_OnButtonKeypadClick_2)
    {
        Vowel_0_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 0);
        Assert::IsTrue(isIncorrectButton == true);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }
#pragma endregion

#pragma region Vowel_1_Strike
    void Vowel_1_Strike_Setup()
    {
        sys_host::SerialNum.SetValue("KA2");
        sys_host::StrikeNum.SetValue(1);

        ChooseTable();

        Init();
        AutoUpdate();
    }

    TEST_METHOD(TEST_Vowel_1_Strike_OnButtonKeypadClick_1)
    {
        Vowel_1_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }

    TEST_METHOD(TEST_Vowel_1_Strike_OnButtonKeypadClick_2)
    {
        Vowel_1_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 0);
        Assert::IsTrue(isIncorrectButton == true);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }
#pragma endregion

#pragma region Vowel_2_Strike
    void Vowel_2_Strike_Setup()
    {
        sys_host::SerialNum.SetValue("KA2");
        sys_host::StrikeNum.SetValue(2);

        ChooseTable();

        Init();
        AutoUpdate();
    }

    TEST_METHOD(TEST_Vowel_2_Strike_OnButtonKeypadClick_1)
    {
        Vowel_2_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }

    TEST_METHOD(TEST_Vowel_2_Strike_OnButtonKeypadClick_2)
    {
        Vowel_2_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 0);
        Assert::IsTrue(isIncorrectButton == true);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }
#pragma endregion

#pragma region WithoutVowel_0_Strike
    void WithoutVowel_0_Strike_Setup()
    {
        sys_host::SerialNum.SetValue("KX2");
        sys_host::StrikeNum.SetValue(0);

        ChooseTable();

        Init();
        AutoUpdate();
    }

    TEST_METHOD(TEST_WithoutVowel_0_Strike_OnButtonKeypadClick_1)
    {
        WithoutVowel_0_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }

    TEST_METHOD(TEST_WithoutVowel_0_Strike_OnButtonKeypadClick_2)
    {
        WithoutVowel_0_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 0);
        Assert::IsTrue(isIncorrectButton == true);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }
#pragma endregion

#pragma region WithoutVowel_1_Strike
    void WithoutVowel_1_Strike_Setup()
    {
        sys_host::SerialNum.SetValue("KX2");
        sys_host::StrikeNum.SetValue(1);

        ChooseTable();

        Init();
        AutoUpdate();
    }

    TEST_METHOD(TEST_WithoutVowel_1_Strike_OnButtonKeypadClick_1)
    {
        WithoutVowel_1_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }

    TEST_METHOD(TEST_WithoutVowel_1_Strike_OnButtonKeypadClick_2)
    {
        WithoutVowel_1_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 0);
        Assert::IsTrue(isIncorrectButton == true);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }
#pragma endregion

#pragma region WithoutVowel_2_Strike
    void WithoutVowel_2_Strike_Setup()
    {
        sys_host::SerialNum.SetValue("KX2");
        sys_host::StrikeNum.SetValue(2);

        ChooseTable();

        Init();
        AutoUpdate();
    }

    TEST_METHOD(TEST_WithoutVowel_2_Strike_OnButtonKeypadClick_1)
    {
        WithoutVowel_2_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }

    TEST_METHOD(TEST_WithoutVowel_2_Strike_OnButtonKeypadClick_2)
    {
        WithoutVowel_2_Strike_Setup();

        lv_event_t e = { 0 };

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 0);
        Assert::IsTrue(isIncorrectButton == true);
        AutoUpdate();

        e.current_target = ui_btnYellow;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 1);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnGreen;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 2);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnBlue;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 3);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();

        e.current_target = ui_btnRed;
        OnButtonKeypadClick(&e);
        Assert::IsTrue(currentSelectButtonIndex == 4);
        Assert::IsTrue(isIncorrectButton == false);
        AutoUpdate();
    }
#pragma endregion
};
