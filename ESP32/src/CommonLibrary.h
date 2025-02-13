#include "CommonDataType.h"

#define MAKE_MSG(msg) String_t(#msg)

void SetNotify(String_t);
String_t GetNotify();
void ClearNotify();

void AutoUpdate();

String_t NumToString(uint64_t);
