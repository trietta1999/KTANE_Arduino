#include <windows.h>
#include <CppUnitTest.h>
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
};
