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
        currentRadioChannel = 0;
        sys_gui::SuccessState.SetValue(INCORRECT);
    }

#pragma region Test_FrequencyMapping
    TEST_METHOD(TEST_FrequencyMapping_01)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_02)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_03)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_04)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_05)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_06)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_07)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_08)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_09)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_10)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_11)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_12)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_13)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_14)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_15)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }

    TEST_METHOD(TEST_FrequencyMapping_16)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(32, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();

        Assert::IsTrue(CorrectFrequency.GetValue() == mapTextFrequency[textType]);
    }
#pragma endregion

#pragma region Test_Operation
    TEST_METHOD(TEST_TextType_01)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_02)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_03)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_04)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_05)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_06)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_07)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_08)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_09)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_10)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_11)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_12)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_13)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_14)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_15)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }

    TEST_METHOD(TEST_TextType_16)
    {
        auto textType = (TEXT_TYPE)std::stoi(std::string(__FUNCTION__).substr(24, 2));

        // Create text info
        ut_textInfo = std::make_tuple(textType, map_TEXT_TYPE[textType]);

        // Init data
        Init();
        currentRadioChannel = (uint8_t)textType - 1;

        // Operation
        OnButtonMoveClick(nullptr);
        OnButtonTXClick(nullptr);

        Assert::IsTrue(sys_gui::SuccessState.GetValue() == STATE_CHECKED);
    }
#pragma endregion
};
