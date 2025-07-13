#include "CppUnitTest.h"
#include "CommonData.h"
#include "Library_Test.cpp"
#include "ui/ui_events.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

static Library_Test* testLibrary = nullptr;

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

        testLibrary = new Library_Test();
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {
        lv_deinit();
        delete testLibrary;
    }

    TEST_METHOD_CLEANUP(TESTMETHOD_Cleanup)
    {
        sys_gui::SuccessState.SetValue(INCORRECT);
    }

#pragma region Test_OnButtonClick_Stage1Module
    TEST_METHOD(TEST_OnButtonClick_Stage1Module_1)
    {
        testLibrary->TEST_Stage1Module_1();

        lv_event_t e = { 0 };
        e.current_target = ui_Button2;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage1Module_2)
    {
        testLibrary->TEST_Stage1Module_2();

        lv_event_t e = { 0 };
        e.current_target = ui_Button2;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage1Module_3)
    {
        testLibrary->TEST_Stage1Module_3();

        lv_event_t e = { 0 };
        e.current_target = ui_Button3;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage1Module_4)
    {
        testLibrary->TEST_Stage1Module_4();

        lv_event_t e = { 0 };
        e.current_target = ui_Button4;
        OnButtonClick(&e);
    }
#pragma endregion

#pragma region Test_OnButtonClick_Stage2Module
    TEST_METHOD(TEST_OnButtonClick_Stage2Module_1)
    {
        testLibrary->TEST_Stage2Module_1();

        lv_event_t e = { 0 };
        e.current_target = ui_Button4;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage2Module_2)
    {
        testLibrary->TEST_Stage2Module_2();

        lv_event_t e = { 0 };
        e.current_target = ui_Button2;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage2Module_3)
    {
        testLibrary->TEST_Stage2Module_3();

        lv_event_t e = { 0 };
        e.current_target = ui_Button1;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage2Module_4)
    {
        testLibrary->TEST_Stage2Module_4();

        lv_event_t e = { 0 };
        e.current_target = ui_Button2;
        OnButtonClick(&e);
    }
#pragma endregion

#pragma region Test_OnButtonClick_Stage3Module
    TEST_METHOD(TEST_OnButtonClick_Stage3Module_1)
    {
        testLibrary->TEST_Stage3Module_1();

        lv_event_t e = { 0 };
        e.current_target = ui_Button2;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage3Module_2)
    {
        testLibrary->TEST_Stage3Module_2();

        lv_event_t e = { 0 };
        e.current_target = ui_Button3;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage3Module_3)
    {
        testLibrary->TEST_Stage3Module_3();

        lv_event_t e = { 0 };
        e.current_target = ui_Button3;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage3Module_4)
    {
        testLibrary->TEST_Stage3Module_4();

        lv_event_t e = { 0 };
        e.current_target = ui_Button4;
        OnButtonClick(&e);
    }
#pragma endregion

#pragma region Test_OnButtonClick_Stage4Module
    TEST_METHOD(TEST_OnButtonClick_Stage4Module_1)
    {
        testLibrary->TEST_Stage4Module_1();

        lv_event_t e = { 0 };
        e.current_target = ui_Button2;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage4Module_2)
    {
        testLibrary->TEST_Stage4Module_2();

        lv_event_t e = { 0 };
        e.current_target = ui_Button1;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage4Module_3)
    {
        testLibrary->TEST_Stage4Module_3();

        lv_event_t e = { 0 };
        e.current_target = ui_Button3;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage4Module_4)
    {
        testLibrary->TEST_Stage4Module_4();

        lv_event_t e = { 0 };
        e.current_target = ui_Button3;
        OnButtonClick(&e);
    }
#pragma endregion

#pragma region Test_OnButtonClick_Stage5Module
    TEST_METHOD(TEST_OnButtonClick_Stage5Module_1)
    {
        testLibrary->TEST_Stage5Module_1();

        lv_event_t e = { 0 };
        e.current_target = ui_Button3;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage5Module_2)
    {
        testLibrary->TEST_Stage5Module_2();

        lv_event_t e = { 0 };
        e.current_target = ui_Button2;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage5Module_3)
    {
        testLibrary->TEST_Stage5Module_3();

        lv_event_t e = { 0 };
        e.current_target = ui_Button4;
        OnButtonClick(&e);
    }

    TEST_METHOD(TEST_OnButtonClick_Stage5Module_4)
    {
        testLibrary->TEST_Stage5Module_4();

        lv_event_t e = { 0 };
        e.current_target = ui_Button1;
        OnButtonClick(&e);
    }
#pragma endregion
};
