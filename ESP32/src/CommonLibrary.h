/**
 * @brief Common library
 */

#ifndef _COMMON_LIBRARY_H
#define _COMMON_LIBRARY_H

#include "CommonDataType.h"

// Do not modify
#pragma endregion
void Init();
void AutoUpdate();
#pragma endregion

// Allow modification
#pragma region Custom_function
String_t NumToString(uint64_t);
#pragma region System_function

#endif // !_COMMON_LIBRARY_H
