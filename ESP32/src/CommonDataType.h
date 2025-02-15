/**
 * @brief Common data type
 */

#ifndef _COMMON_DATATYPE_H
#define _COMMON_DATATYPE_H

#ifdef _WIN64 // STD data type
#include <string>
#define String_t std::string
#else // Arduino data type
#include <Arduino.h>
#define String_t String
#endif

#endif // !_COMMON_DATATYPE_H
