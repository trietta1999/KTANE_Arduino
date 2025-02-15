/**
 * @brief Common data
 */

#ifdef _WIN64
#include <cstdint>
#endif
#include "CData.h"
#include "CommonDataType.h"

/* TODO: Declare shared data for the system
         Use "extern" and do not declare initial values
*/

extern CData<uint16_t> Button2Value;
extern CData<int32_t> SliderValue;
extern CData<int32_t> ArcValue;
extern CData<uint16_t> CheckboxValue;
extern CData<String_t> DropdownValue;
extern CData<uint16_t> SwitchValue;
extern CData<String_t> RollerValue;
