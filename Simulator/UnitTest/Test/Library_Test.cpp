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

#pragma region Test_3Wire
    TEST_METHOD(TEST_WireModule_3wire_1)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLUE });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::SECOND_WIRE);
    }

    TEST_METHOD(TEST_WireModule_3wire_2)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::WHITE });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::THIRD_WIRE);
    }

    TEST_METHOD(TEST_WireModule_3wire_3)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::SECOND_WIRE);
    }

    TEST_METHOD(TEST_WireModule_3wire_4)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::THIRD_WIRE);
    }
#pragma endregion

#pragma region Test_4Wire
    TEST_METHOD(TEST_WireModule_4wire_1)
    {
        sys_host::SerialNum.SetValue("ABCDEF5");
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::FOURTH_WIRE);
    }

    TEST_METHOD(TEST_WireModule_4wire_2)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::YELLOW });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::SECOND_WIRE);
    }

    TEST_METHOD(TEST_WireModule_4wire_3)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::YELLOW });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::FIRST_WIRE);
    }

    TEST_METHOD(TEST_WireModule_4wire_4)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::YELLOW });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::FOURTH_WIRE);
    }

    TEST_METHOD(TEST_WireModule_4wire_5)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::BLACK });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::SECOND_WIRE);
    }
#pragma endregion

#pragma region Test_5Wire
    TEST_METHOD(TEST_WireModule_5wire_1)
    {
        sys_host::SerialNum.SetValue("ABCDEF5");
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::BLACK });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::FOURTH_WIRE);
    }

    TEST_METHOD(TEST_WireModule_5wire_2)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::RED });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::FIRST_WIRE);
    }

    TEST_METHOD(TEST_WireModule_5wire_3)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::RED });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::SECOND_WIRE);
    }

    TEST_METHOD(TEST_WireModule_5wire_4)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::RED });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::FIRST_WIRE);
    }
#pragma endregion

#pragma region Test_6Wire
    TEST_METHOD(TEST_WireModule_6wire_1)
    {
        sys_host::SerialNum.SetValue("ABCDEF5");
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::WHITE });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::THIRD_WIRE);
    }

    TEST_METHOD(TEST_WireModule_6wire_2)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::RED, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::WHITE, WIRECOLOR_TYPE::WHITE });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::FOURTH_WIRE);
    }

    TEST_METHOD(TEST_WireModule_6wire_3)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::WHITE });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::SIXTH_WIRE);
    }

    TEST_METHOD(TEST_WireModule_6wire_4)
    {
        WireColorList.SetValue({ WIRECOLOR_TYPE::BLUE, WIRECOLOR_TYPE::PINK, WIRECOLOR_TYPE::WHITE, WIRECOLOR_TYPE::BLACK, WIRECOLOR_TYPE::YELLOW, WIRECOLOR_TYPE::WHITE });
        WireModule();
        Assert::IsTrue(CorrectWireIndex.GetValue() == WIRE_IN_ORDER::FOURTH_WIRE);
    }
#pragma endregion
};
