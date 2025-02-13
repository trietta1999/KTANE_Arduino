/**
 * @brief Common library
 */

#include "CommonLibrary.h"
#include "CommonData.h"

String_t NumToString(uint64_t value)
{
#ifdef _WIN64
    return std::to_string(value);
#else
    return String(value);
#endif
}
