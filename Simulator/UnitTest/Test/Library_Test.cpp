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

    TEST_METHOD_INITIALIZE(TESTMETHOD_Init)
    {
        WireColorList.SetValue({ });
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

    TEST_METHOD(TEST_CreateRandomWireEnableList)
    {
        uint8_t size = 10;
        auto result = CreateRandomWireEnableList(10);

        Assert::IsTrue(result.size() == size);
        Assert::IsTrue(std::count(result.begin(), result.end(), true) >= WIRE_NUM_MIN);
        Assert::IsTrue(std::count(result.begin(), result.end(), true) < WIRE_NUM_MAX + 1);
    }

    TEST_METHOD(TEST_CreateRandomWireColorList)
    {
        std::vector<bool> listEnable = { true, false, true, true, false, false, };
        auto result = CreateRandomWireColorList(listEnable);
        auto colorList = WireColorList.GetValue();

        Assert::IsTrue(result.size() == listEnable.size());
        Assert::IsTrue(
            std::count(result.begin(), result.end(), WIRECOLOR_TYPE::MIN) == std::count(listEnable.begin(), listEnable.end(), false)
        );
        Assert::IsTrue(
            colorList.size() == (result.size() - (uint8_t)std::count(result.begin(), result.end(), WIRECOLOR_TYPE::MIN))
        );
    }
};
