/**
 * @brief Common library
 */

#include "CommonLibrary.h"
#include "CommonData.h"
#include "CData.cpp"

String_t NumToString(uint64_t value)
{
#ifdef _WIN64
    return std::to_string(value);
#else
    return String(value);
#endif
}

void SetStrike(bool state)
{
    StrikeState_GUI.SetValue(state);
    StrikeState_HARD.SetValue(state);
}
