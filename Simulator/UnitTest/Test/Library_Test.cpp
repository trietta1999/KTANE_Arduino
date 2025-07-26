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

    TEST_METHOD(TEST_GenerateRandomString_1)
    {
        auto result = GenerateRandomString(5, 'A');

        Assert::IsTrue(result[0] == 'A');
        Assert::IsTrue(result.length() == 9);
    }

    TEST_METHOD(TEST_GenerateRandomString_2)
    {
        auto result = GenerateRandomString(10, 'A');

        Assert::IsTrue(result[0] == 'A');
        Assert::IsTrue(result.length() == 19);
    }
};
