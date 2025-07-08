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

    TEST_METHOD(TEST_FlatMorseCodeArray)
    {
        std::vector<std::array<int32_t, MAX_MORSE_SYMBOL>> list = {
            { 1, 1, 1, 1, 1 },
            { 0, 0, 0, 0, 0 },
            { 1, 0, 1, 0, 1 },
        };
        auto result = FlatMorseCodeArray(list);
        std::vector<int32_t> compare = { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 };

        Assert::IsTrue(result == compare);
    }

    TEST_METHOD(TEST_ConvertSymbolToDigitArray)
    {
        auto result = ConvertSymbolToDigitArray("-.-.-");
        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { DASH_LEVEL, DOT_LEVEL, DASH_LEVEL, DOT_LEVEL, DASH_LEVEL };

        Assert::IsTrue(result == compare);
    }

#pragma region Test_ConvertTextToMorseCode
    TEST_METHOD(TEST_ConvertTextToMorseCode_A)
    {
        auto result = ConvertTextToMorseCode("A");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_B)
    {
        auto result = ConvertTextToMorseCode("B");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DOT_LEVEL;
        compare[3] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_C)
    {
        auto result = ConvertTextToMorseCode("C");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DASH_LEVEL;
        compare[3] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_D)
    {
        auto result = ConvertTextToMorseCode("D");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_E)
    {
        auto result = ConvertTextToMorseCode("E");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_F)
    {
        auto result = ConvertTextToMorseCode("F");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DASH_LEVEL;
        compare[3] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_G)
    {
        auto result = ConvertTextToMorseCode("G");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DASH_LEVEL;
        compare[2] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_H)
    {
        auto result = ConvertTextToMorseCode("H");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DOT_LEVEL;
        compare[3] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_I)
    {
        auto result = ConvertTextToMorseCode("I");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_J)
    {
        auto result = ConvertTextToMorseCode("J");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DASH_LEVEL;
        compare[2] = DASH_LEVEL;
        compare[3] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_K)
    {
        auto result = ConvertTextToMorseCode("K");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_L)
    {
        auto result = ConvertTextToMorseCode("L");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DASH_LEVEL;
        compare[2] = DOT_LEVEL;
        compare[3] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_M)
    {
        auto result = ConvertTextToMorseCode("M");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_N)
    {
        auto result = ConvertTextToMorseCode("N");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_O)
    {
        auto result = ConvertTextToMorseCode("O");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DASH_LEVEL;
        compare[2] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_P)
    {
        auto result = ConvertTextToMorseCode("P");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DASH_LEVEL;
        compare[2] = DASH_LEVEL;
        compare[3] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_Q)
    {
        auto result = ConvertTextToMorseCode("Q");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DASH_LEVEL;
        compare[2] = DOT_LEVEL;
        compare[3] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_R)
    {
        auto result = ConvertTextToMorseCode("R");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DASH_LEVEL;
        compare[2] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_S)
    {
        auto result = ConvertTextToMorseCode("S");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_T)
    {
        auto result = ConvertTextToMorseCode("T");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_U)
    {
        auto result = ConvertTextToMorseCode("U");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_V)
    {
        auto result = ConvertTextToMorseCode("V");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DOT_LEVEL;
        compare[3] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_W)
    {
        auto result = ConvertTextToMorseCode("W");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DOT_LEVEL;
        compare[1] = DASH_LEVEL;
        compare[2] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_X)
    {
        auto result = ConvertTextToMorseCode("X");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DOT_LEVEL;
        compare[3] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_Y)
    {
        auto result = ConvertTextToMorseCode("Y");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DOT_LEVEL;
        compare[2] = DASH_LEVEL;
        compare[3] = DASH_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }

    TEST_METHOD(TEST_ConvertTextToMorseCode_Z)
    {
        auto result = ConvertTextToMorseCode("Z");

        std::array<int32_t, MAX_MORSE_SYMBOL> compare = { SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL, SPACE_LEVEL };
        compare[0] = DASH_LEVEL;
        compare[1] = DASH_LEVEL;
        compare[2] = DOT_LEVEL;
        compare[3] = DOT_LEVEL;

        Assert::IsTrue(result[0] == compare);
    }
#pragma endregion
};
