#include "CommonLibrary.h"
#include "CommonData.h"

void SetNotify(String_t msg)
{
    Message = msg;
}

String_t GetNotify()
{
    return Message;
}

void ClearNotify()
{
    Message = "";
}

String_t NumToString(uint64_t value)
{
#ifdef _WIN64
    return std::to_string(value);
#else
    return String(value);
#endif
}
