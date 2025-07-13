#include <windows.h>
#include <CppUnitTest.h>
#include "CommonData.h"
#include "CommonLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(Library_Test)
{
public:
    TEST_CLASS_INITIALIZE(TESTCLASS_Init)
    {

    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {

    }

    TEST_METHOD(TEST_RandomRange_1)
    {
        for (uint16_t i = 0; i < 1000; i++)
        {
            uint8_t value = RandomRange(5, 10);

            if (value >= 10)
            {
                wchar_t msg[100];
                wsprintf(msg, L"Value %d is out of range", value);
                Assert::Fail(msg);
                return;
            }
        }
    }

    TEST_METHOD(TEST_RandomRange_2)
    {
        Assert::IsTrue(RandomRange(5, 6) == 5);
    }

    TEST_METHOD(TEST_GenerateSerialNumber)
    {
        std::string serial = GenerateSerialNumber();

        Assert::IsTrue(std::isdigit(serial.back()));
    }

    TEST_METHOD(TEST_VowelCheck_1)
    {
        Assert::IsTrue(VowelCheck("QWRTEHN") == true);
    }

    TEST_METHOD(TEST_VowelCheck_2)
    {
        Assert::IsTrue(VowelCheck("QWRTNHN") == false);
    }

    TEST_METHOD(TEST_OddCheckAtLast_1)
    {
        Assert::IsTrue(OddCheckAtLast("QWRTEHN2") == false);
    }

    TEST_METHOD(TEST_OddCheckAtLast_2)
    {
        Assert::IsTrue(OddCheckAtLast("QWRTEHN1") == true);
    }

    TEST_METHOD(TEST_NumberCheckInTimer_1)
    {
        sys_host::TimeClock.SetValue(std::make_pair(12, 34));
        Assert::IsTrue(NumberCheckInTimer(1) == true);
    }

    TEST_METHOD(TEST_NumberCheckInTimer_2)
    {
        sys_host::TimeClock.SetValue(std::make_pair(12, 34));
        Assert::IsTrue(NumberCheckInTimer(2) == true);
    }

    TEST_METHOD(TEST_NumberCheckInTimer_3)
    {
        sys_host::TimeClock.SetValue(std::make_pair(12, 34));
        Assert::IsTrue(NumberCheckInTimer(3) == true);
    }

    TEST_METHOD(TEST_NumberCheckInTimer_4)
    {
        sys_host::TimeClock.SetValue(std::make_pair(12, 34));
        Assert::IsTrue(NumberCheckInTimer(4) == true);
    }

    TEST_METHOD(TEST_NumberCheckInTimer_5)
    {
        sys_host::TimeClock.SetValue(std::make_pair(12, 34));
        Assert::IsTrue(NumberCheckInTimer(5) == false);
    }

    TEST_METHOD(TEST_NumberCheckInTimer_6)
    {
        sys_host::TimeClock.SetValue(std::make_pair(22, 22));
        Assert::IsTrue(NumberCheckInTimer(2) == true);
    }

#pragma region Test_Stage1Module
    void Test_Stage1Module_Setup()
    {
        CurrentStage.SetValue(1);
    }

    TEST_METHOD(TEST_Stage1Module_1)
    {
        Test_Stage1Module_Setup();

        Stage1Module(1, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::SECOND);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 2);
    }

    TEST_METHOD(TEST_Stage1Module_2)
    {
        Test_Stage1Module_Setup();

        Stage1Module(2, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::SECOND);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 2);
    }

    TEST_METHOD(TEST_Stage1Module_3)
    {
        Test_Stage1Module_Setup();

        Stage1Module(3, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::THIRD);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 3);
    }

    TEST_METHOD(TEST_Stage1Module_4)
    {
        Test_Stage1Module_Setup();

        Stage1Module(4, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::FOURTH);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 4);
    }
#pragma endregion

#pragma region Test_Stage2Module
    void Test_Stage2Module_Setup()
    {
        CurrentStage.SetValue(2);
        ListStageData.SetValue({ { POSTION_TYPE::SECOND, 3 } });
    }

    TEST_METHOD(TEST_Stage2Module_1)
    {
        Test_Stage2Module_Setup();

        Stage2Module(1, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::FOURTH);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 4);
    }

    TEST_METHOD(TEST_Stage2Module_2)
    {
        Test_Stage2Module_Setup();

        Stage2Module(2, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::SECOND);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 2);
    }

    TEST_METHOD(TEST_Stage2Module_3)
    {
        Test_Stage2Module_Setup();

        Stage2Module(3, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::FIRST);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 1);
    }

    TEST_METHOD(TEST_Stage2Module_4)
    {
        Test_Stage2Module_Setup();

        Stage2Module(4, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::SECOND);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 2);
    }
#pragma endregion

#pragma region Test_Stage3Module
    void Test_Stage3Module_Setup()
    {
        CurrentStage.SetValue(3);
        ListStageData.SetValue({
            { POSTION_TYPE::SECOND, 3 },
            { POSTION_TYPE::THIRD, 2 },
            });
    }

    TEST_METHOD(TEST_Stage3Module_1)
    {
        Test_Stage3Module_Setup();

        Stage3Module(1, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::SECOND);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 2);
    }

    TEST_METHOD(TEST_Stage3Module_2)
    {
        Test_Stage3Module_Setup();

        Stage3Module(2, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::THIRD);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 3);
    }

    TEST_METHOD(TEST_Stage3Module_3)
    {
        Test_Stage3Module_Setup();

        Stage3Module(3, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::THIRD);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 3);
    }

    TEST_METHOD(TEST_Stage3Module_4)
    {
        Test_Stage3Module_Setup();

        Stage3Module(4, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::FOURTH);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 4);
    }
#pragma endregion

#pragma region Test_Stage4Module
    void Test_Stage4Module_Setup()
    {
        CurrentStage.SetValue(4);
        ListStageData.SetValue({
            { POSTION_TYPE::SECOND, 3 },
            { POSTION_TYPE::THIRD, 2 },
            { POSTION_TYPE::FOURTH, 1 },
            });
    }

    TEST_METHOD(TEST_Stage4Module_1)
    {
        Test_Stage4Module_Setup();

        Stage4Module(1, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::SECOND);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 2);
    }

    TEST_METHOD(TEST_Stage4Module_2)
    {
        Test_Stage4Module_Setup();

        Stage4Module(2, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::FIRST);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 1);
    }

    TEST_METHOD(TEST_Stage4Module_3)
    {
        Test_Stage4Module_Setup();

        Stage4Module(3, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::THIRD);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 3);
    }

    TEST_METHOD(TEST_Stage4Module_4)
    {
        Test_Stage4Module_Setup();

        Stage4Module(4, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::THIRD);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 3);
    }
#pragma endregion

#pragma region Test_Stage5Module
    void Test_Stage5Module_Setup()
    {
        CurrentStage.SetValue(5);
        ListStageData.SetValue({
            { POSTION_TYPE::SECOND, 3 },
            { POSTION_TYPE::THIRD, 2 },
            { POSTION_TYPE::FOURTH, 1 },
            { POSTION_TYPE::FIRST, 4 },
            });
    }

    TEST_METHOD(TEST_Stage5Module_1)
    {
        Test_Stage5Module_Setup();

        Stage5Module(1, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::THIRD);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 3);
    }

    TEST_METHOD(TEST_Stage5Module_2)
    {
        Test_Stage5Module_Setup();

        Stage5Module(2, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::SECOND);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 2);
    }

    TEST_METHOD(TEST_Stage5Module_3)
    {
        Test_Stage5Module_Setup();

        Stage5Module(3, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::FOURTH);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 4);
    }

    TEST_METHOD(TEST_Stage5Module_4)
    {
        Test_Stage5Module_Setup();

        Stage5Module(4, { 1, 2, 3, 4 });

        Assert::IsTrue(std::get<POSITION_POS>(CurrentCorrectData.GetValue()) == POSTION_TYPE::FIRST);
        Assert::IsTrue(std::get<VALUE_POS>(CurrentCorrectData.GetValue()) == 1);
    }
#pragma endregion
};
