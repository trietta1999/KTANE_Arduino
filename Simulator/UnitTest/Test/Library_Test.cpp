#include <windows.h>
#include <CppUnitTest.h>
#include "CommonData.h"
#include "CommonLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(Library_Test)
{
public:
    decltype(mapColorSequence) mapColorSequence_backup;

    TEST_CLASS_INITIALIZE(TESTCLASS_Init)
    {
        CurrentStage.SetValue(4);
        ColorList.SetValue({ COLOR_TYPE::RED, COLOR_TYPE::BLUE, COLOR_TYPE::GREEN, COLOR_TYPE::YELLOW });
    }

    TEST_CLASS_CLEANUP(TESTCLASS_Cleanup)
    {

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

    TEST_METHOD(TEST_StageGenerator)
    {
        auto result = StageGenerator(10);

        Assert::IsTrue(result.size() == 10);
    }

    TEST_METHOD(TEST_SequenceGenerator_1)
    {
        sys_host::SerialNum.SetValue("KA2");
        sys_host::StrikeNum.SetValue(0);

        ChooseTable();

        auto result = SequenceGenerator();

        Assert::IsTrue(result[0] == COLOR_TYPE::BLUE);
        Assert::IsTrue(result[1] == COLOR_TYPE::RED);
        Assert::IsTrue(result[2] == COLOR_TYPE::YELLOW);
        Assert::IsTrue(result[3] == COLOR_TYPE::GREEN);

        ResetTable();
    }

    TEST_METHOD(TEST_SequenceGenerator_2)
    {
        sys_host::SerialNum.SetValue("KA2");
        sys_host::StrikeNum.SetValue(1);

        ChooseTable();

        auto result = SequenceGenerator();

        Assert::IsTrue(result[0] == COLOR_TYPE::YELLOW);
        Assert::IsTrue(result[1] == COLOR_TYPE::GREEN);
        Assert::IsTrue(result[2] == COLOR_TYPE::BLUE);
        Assert::IsTrue(result[3] == COLOR_TYPE::RED);

        ResetTable();
    }

    TEST_METHOD(TEST_SequenceGenerator_3)
    {
        sys_host::SerialNum.SetValue("KA2");
        sys_host::StrikeNum.SetValue(2);

        ChooseTable();

        auto result = SequenceGenerator();

        Assert::IsTrue(result[0] == COLOR_TYPE::GREEN);
        Assert::IsTrue(result[1] == COLOR_TYPE::RED);
        Assert::IsTrue(result[2] == COLOR_TYPE::YELLOW);
        Assert::IsTrue(result[3] == COLOR_TYPE::BLUE);

        ResetTable();
    }

    TEST_METHOD(TEST_SequenceGenerator_4)
    {
        sys_host::SerialNum.SetValue("KX2");
        sys_host::StrikeNum.SetValue(0);

        ChooseTable();

        auto result = SequenceGenerator();

        Assert::IsTrue(result[0] == COLOR_TYPE::BLUE);
        Assert::IsTrue(result[1] == COLOR_TYPE::YELLOW);
        Assert::IsTrue(result[2] == COLOR_TYPE::GREEN);
        Assert::IsTrue(result[3] == COLOR_TYPE::RED);

        ResetTable();
    }

    TEST_METHOD(TEST_SequenceGenerator_5)
    {
        sys_host::SerialNum.SetValue("KX2");
        sys_host::StrikeNum.SetValue(1);

        ChooseTable();

        auto result = SequenceGenerator();

        Assert::IsTrue(result[0] == COLOR_TYPE::RED);
        Assert::IsTrue(result[1] == COLOR_TYPE::BLUE);
        Assert::IsTrue(result[2] == COLOR_TYPE::YELLOW);
        Assert::IsTrue(result[3] == COLOR_TYPE::GREEN);

        ResetTable();
    }

    TEST_METHOD(TEST_SequenceGenerator_6)
    {
        sys_host::SerialNum.SetValue("KX2");
        sys_host::StrikeNum.SetValue(2);

        ChooseTable();

        auto result = SequenceGenerator();

        Assert::IsTrue(result[0] == COLOR_TYPE::YELLOW);
        Assert::IsTrue(result[1] == COLOR_TYPE::GREEN);
        Assert::IsTrue(result[2] == COLOR_TYPE::BLUE);
        Assert::IsTrue(result[3] == COLOR_TYPE::RED);

        ResetTable();
    }
};
