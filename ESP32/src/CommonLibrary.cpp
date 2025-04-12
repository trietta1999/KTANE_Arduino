/**
 * @brief Common library
 */

#include "CommonLibrary.h"
#include "CommonData.h"

 // Do not delete or rename
#pragma region System_function
void SetStrike(bool state)
{
    StrikeState_GUI.SetValue(state);
    StrikeState_HW.SetValue(state);
}
#pragma endregion

// Allow modification
#pragma region Custom_function

#pragma endregion
