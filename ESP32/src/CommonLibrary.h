/**
 * @brief Common library
 */

#include "CommonDataType.h"

#define MAKE_MSG(msg) String_t(#msg)

// Do not modify
#pragma region System_function
void Init();
void AutoUpdate();
#pragma endregion

// Allow modification
#pragma region Custom_function
String_t NumToString(uint64_t);
#pragma endregion
