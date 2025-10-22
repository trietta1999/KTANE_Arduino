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

    TEST_METHOD(TEST_CreateValidWireIndexList)
    {
        auto result = CreateValidWireIndexList(5, 20);

        Assert::IsTrue(result.size() == 20);
        Assert::IsTrue(std::count(result.begin(), result.end(), true) >= 5);
        Assert::IsTrue(std::count(result.begin(), result.end(), true) <= 20);
    }

/* Test case refered to https://ktane.fandom.com/wiki/Complicated_Wires#Optimized_(LeGeND/Lebossle) */

#pragma region Test_White
    TEST_METHOD(TEST_White_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::WHITE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = false,
            .star = false,
        };

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }

    TEST_METHOD(TEST_White_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::WHITE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = false,
            .star = true,
        };

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }

    TEST_METHOD(TEST_White_3)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::WHITE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = false,
        };

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }

    TEST_METHOD(TEST_White_4_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::WHITE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = true,
        };

        sys_host::BatteryNum.SetValue(2);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }

    TEST_METHOD(TEST_White_4_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::WHITE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = true,
        };

        sys_host::BatteryNum.SetValue(1);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }
#pragma endregion

#pragma region Test_Red
    TEST_METHOD(TEST_Red_1_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::RED,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = false,
            .star = false,
        };

        sys_host::SerialNum.SetValue("A2");

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }
    TEST_METHOD(TEST_Red_1_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::RED,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = false,
            .star = false,
        };

        sys_host::SerialNum.SetValue("A3");

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }

    TEST_METHOD(TEST_Red_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::RED,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = false,
            .star = true,
        };

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }

    TEST_METHOD(TEST_Red_3_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::RED,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = false,
        };

        sys_host::BatteryNum.SetValue(2);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }

    TEST_METHOD(TEST_Red_3_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::RED,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = false,
        };

        sys_host::BatteryNum.SetValue(1);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }

    TEST_METHOD(TEST_Red_4_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::RED,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = true,
        };

        sys_host::BatteryNum.SetValue(2);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }

    TEST_METHOD(TEST_Red_4_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::RED,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = true,
        };

        sys_host::BatteryNum.SetValue(1);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }
#pragma endregion

#pragma region Test_Blue
    TEST_METHOD(TEST_Blue_1_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = false,
            .star = false,
        };

        sys_host::SerialNum.SetValue("A2");

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }
    TEST_METHOD(TEST_Blue_1_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = false,
            .star = false,
        };

        sys_host::SerialNum.SetValue("A3");

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }

    TEST_METHOD(TEST_Blue_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = false,
            .star = true,
        };

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }

    TEST_METHOD(TEST_Blue_3_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = false,
        };

        sys_host::ComPortType.SetValue(COMPORT_TYPE::Parallel);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }

    TEST_METHOD(TEST_Blue_3_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = false,
        };

        sys_host::ComPortType.SetValue(COMPORT_TYPE::PS2);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }

    TEST_METHOD(TEST_Blue_4_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = true,
        };

        sys_host::ComPortType.SetValue(COMPORT_TYPE::Parallel);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }

    TEST_METHOD(TEST_Blue_4_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::MIN,
            .led = true,
            .star = true,
        };

        sys_host::ComPortType.SetValue(COMPORT_TYPE::PS2);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }
#pragma endregion

#pragma region Test_2Colors
    TEST_METHOD(TEST_2Colors_1_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::RED,
            .led = false,
            .star = false,
        };

        sys_host::SerialNum.SetValue("A2");

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }
    TEST_METHOD(TEST_2Colors_1_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::RED,
            .led = false,
            .star = false,
        };

        sys_host::SerialNum.SetValue("A3");

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }

    TEST_METHOD(TEST_2Colors_2_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::RED,
            .led = false,
            .star = true,
        };

        sys_host::ComPortType.SetValue(COMPORT_TYPE::Parallel);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }

    TEST_METHOD(TEST_2Colors_2_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::RED,
            .led = false,
            .star = true,
        };

        sys_host::ComPortType.SetValue(COMPORT_TYPE::PS2);

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }

    TEST_METHOD(TEST_2Colors_3_1)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::RED,
            .led = true,
            .star = false,
        };

        sys_host::SerialNum.SetValue("A2");

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, true);
    }

    TEST_METHOD(TEST_2Colors_3_2)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::RED,
            .led = true,
            .star = false,
        };

        sys_host::SerialNum.SetValue("A3");

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }

    TEST_METHOD(TEST_2Colors_4)
    {
        wire_t wire = {
            .color1 = WIRECOLOR_TYPE::BLUE,
            .color2 = WIRECOLOR_TYPE::RED,
            .led = true,
            .star = true,
        };

        CheckWire(wire);

        Assert::AreEqual(wire.canCut, false);
    }
#pragma endregion
};
