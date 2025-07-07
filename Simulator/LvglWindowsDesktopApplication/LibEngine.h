/**
 * @file  LibEngine.h
 * @brief Library engine header
 */

#include "..\LvglPlatform\lvgl\src\misc\lv_types.h"
#include "CommonDataType.h"

#pragma once
void ThreeWiresModule();
void FourWiresModule();
void FiveWiresModule();
void SixWiresModule();
int CountElementOccurences(std::vector<COLOR> wireColorList, WIRECOLOR_TYPE color);
